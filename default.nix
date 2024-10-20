{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.sfml
  ];

  shellHook = ''
    mkdir -p build
    cd build
    cmake ..
    make
  '';
}