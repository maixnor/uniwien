local CONSTANT_TCP_PORT = 1234
local osue_protocol = Proto("osue", "OS UE Protocol")

local OSUE_PROTO_OP = {
	[0] = "ADD",
	[1] = "SUB",
	[2] = "MUL",
	[3] = "LEFT_SHIFT",
	[4] = "RIGHT_SHIFT"
}

local OSUE_MSG_TYPE = {
	[0] = "CHALLENGE",
	[1] = "SERVER_INFO"
}

local OSUE_SERVER_INFO = {
	[0] = "CORRECT",
	[1] = "WRONG"
}

osue_protocol.fields.message_type = ProtoField.uint32("osue.message_unit.msg_type", "Message Type", base.HEX, OSUE_MSG_TYPE)
osue_protocol.fields.server_info = ProtoField.uint32("osue.message_unit.server_info", "Server Info", base.HEX, OSUE_SERVER_INFO)

osue_protocol.fields.op = ProtoField.uint32("osue.proto_unit.op", "Protocol Operator", base.HEX, OSUE_PROTO_OP)
osue_protocol.fields.lhs = ProtoField.uint32("osue.proto_unit.lhs", "Protocol Operand 1 (left hand side)", base.DEC)
osue_protocol.fields.rhs = ProtoField.uint32("osue.proto_unit.rhs", "Protocol Operand 2 (right hand side)", base.DEC)
osue_protocol.fields.answer = ProtoField.uint32("osue.proto_unit.answer", "Protocol Answer (result)", base.DEC)

-- some special conditions are handled through return values
-- documentation used:
-- https://wiki.wireshark.org/Lua/Dissectors,
-- https://www.wireshark.org/docs/wsdg_html_chunked/lua_module_Tvb.html

function osue_protocol.dissector(buffer, pinfo, tree)
	pinfo.cols.protocol = osue_protocol.name
	local subtree = tree:add(osue_protocol, buffer(), "OS UE Protocol")

	-- ignore cut-off packets
	if buffer:len() < buffer:reported_len() then
		return 0
	end

	local buf_len = buffer:len()

	-- initialize index for the start of our protocol message(s)
	local proto_start = 0
	-- loop through all protocol messages
	while proto_start < buf_len do
		-- would not be a valid protocol message anymore (min length of 8 bytes)
		if buf_len - proto_start < 8 then
			return 0
		end

		local msg_type = buffer(proto_start, 4):le_uint()
		subtree:add_le(osue_protocol.fields.message_type, buffer(proto_start, 4))
		if OSUE_MSG_TYPE[msg_type] == "CHALLENGE" then
			if buf_len - proto_start < 24 then
				return
			end
			subtree:add_le(osue_protocol.fields.op, buffer(proto_start + 8, 4))
			subtree:add_le(osue_protocol.fields.lhs, buffer(proto_start + 12, 4))
			subtree:add_le(osue_protocol.fields.rhs, buffer(proto_start + 16, 4))
			subtree:add_le(osue_protocol.fields.answer, buffer(proto_start + 20, 4))
			proto_start = proto_start + 24
		elseif OSUE_MSG_TYPE[msg_type] == "SERVER_INFO" then
			subtree:add_le(osue_protocol.fields.server_info, buffer(proto_start + 4, 4))
			proto_start = proto_start + 8
		else
			payloadtree:set_text("Unknown message type!")
			return 0
		end
	end -- of while
end -- osue_protocol.dissector

local tcp_port = DissectorTable.get("tcp.port")
tcp_port:add(CONSTANT_TCP_PORT, osue_protocol)
