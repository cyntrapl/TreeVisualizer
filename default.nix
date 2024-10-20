{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.sfml
  ];

  shellHook = ''
    cmake -B build -S .
    cd build
    make
  '';
}
