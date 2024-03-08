{
  description = "A development environment for Jupyter notebooks with Python";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
        myPythonEnv = pkgs.python3.withPackages (ps: with ps; [
          ipython
          notebook
          jupyterlab
          numpy
          pandas
          matplotlib
          scipy
        ]);
      in
      {
        devShell = pkgs.mkShell {
          buildInputs = [ myPythonEnv pkgs.vscode pkgs.vscode-extensions.ms-python.python ];
          shellCmd = ''
						git pull --all
            code notebooks
						git add .
						git commit -m "snapshot $(date)"
						git push
          '';
        };
      });
}

