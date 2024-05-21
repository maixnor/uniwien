{
  description = "basic env for ADS cpp";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { nixpkgs, ... }: let
    system = "x86_64-linux";
    in {
      devShells."${system}".default = let 
        pkgs = import nixpkgs { 
          inherit system;
        };
      in pkgs.mkShell {

        buildInputs = with pkgs; [
          gcc
        ];
        shellHook = ''
          git pull --all
          alias g++='g++ -Wall -Wextra -Werror -O3 -std=c++17 -pedantic-errors'
          echo "alias set"

          gcc --version
        '';
      };
    };
}
