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
        jupyter = import (pkgs.fetchFromGitHub {                                      
          owner = "tweag";                                                            
          repo = "jupyterWith";                         
          # Replace this with current revision.                              
          rev = "269999caa8d506e93ff56c8643cecb91ded2fdef";                           
          sha256 = "08iig872ay8d711n2gbfzrf496m9x9a9xwr0xca9hn7j61c3xr43";            
          fetchSubmodules = true;                                                     
        }) {};                                                                        
                                                                                      
        kernels = jupyter.kernels;                                                    
                                                                                      
        irkernel = kernels.iRWith {                
          name = "nixpkgs";                                                         
          # Libraries to be available to the kernel.                                
          packages = p: with p; [                                                   
            ggplot2                                                          
          ];                                           
        };                                                                          
                                                                                      
        jupyterEnvironment = (jupyter.jupyterlabWith {                                
          kernels = [ irkernel ];                                                   
        });                                                                         
      in
      {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            jupyterEnvironment.env
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
                # Add any additional Python packages here
                seaborn # a dataset library
              ]
            ))
            gnuplot
            octave
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

              # --wait for the process to not exit immediately
              code --install-extension ms-toolsai.jupyter
              code . --wait
              exit
          '';
        };
      }
    );
}
