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
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;

          config = {
            allowUnfree = true;
          };
        };
      in
      {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            (python3.withPackages (
              ps: with ps; [
                ipython
                ipykernel
                notebook
                jupyterlab
                numpy
                pandas
                matplotlib
                sympy
                scipy
                statsmodels
                seaborn
              ]
            ))
            gnuplot
            octave
            R
            rPackages.tidyverse
            rPackages.ggplot2
            rPackages.rmarkdown
            rPackages.IRkernel
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

                git add .
                git commit -m "snapshot notebooks"
              }
              trap cleanup EXIT

              # Install the R kernel for Jupyter
              R -e 'IRkernel::installspec()'

              # --wait for the process to not exit immediately
              code --install-extension ms-toolsai.jupyter
              code . --wait
              exit
          '';
        };
      }
    );
}
