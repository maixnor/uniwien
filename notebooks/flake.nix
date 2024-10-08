{
  description = "A development environment for Jupyter notebooks with Python and R";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs {
          inherit system;

          config = {
            allowUnfree = true;
          };
        };
        jupyterEnv = pkgs.mkShell {
          buildInputs = with pkgs; [
            (python3.withPackages (
              ps: with ps; [
                ipython
                notebook
                jupyterlab
                numpy
                pandas
                matplotlib
                sympy
                # Add any additional Python packages here
              ]
            ))
            vscodium
          ];
          shellHook = ''
            						git pull --all

                        export PYTHONPATH="${pkgs.python3}/${pkgs.python3.sitePackages}"
                        export JUPYTER_PATH="${pkgs.python3}/${pkgs.python3.sitePackages}"
                        echo "Starting Jupyter server without a password..."
                        jupyter lab --no-browser --ip=127.0.0.1 --port=8888 --NotebookApp.token="" &
                        JUPYTER_PID=$!
                        echo "Jupyter server started with PID $JUPYTER_PID"
                        function cleanup {
                          echo "Stopping Jupyter server..."
                          kill $JUPYTER_PID

            							git add ./notebooks
            							git commit -m "snapshot notebooks"
                        }
                        trap cleanup EXIT

            						# --wait for the process to not exit immediately
            						codium --install-extension ms-toolsai.jupyter
            						codium . --wait
            						exit
          '';
        };
      in
      {
        devShell = jupyterEnv;
      }
    );
}
