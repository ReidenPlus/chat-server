{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  pname = "chat-server";
  version = "1.0.0";

  src = ./.;

  buildInputs = [
    pkgs.cmake
    pkgs.boost
    pkgs.gcc
  ];

  buildPhase = ''
    mkdir build
    cd build
    cmake ..
    make
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp build/chat-server $out/bin/
  '';
}
