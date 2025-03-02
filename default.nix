let
  pkgs = import <nixpkgs> { };
  lib = pkgs.lib;
  kernel = pkgs.linux;
in
let
  kernelModule = pkgs.callPackage ./nix/ffb_wheel_module.nix { inherit kernel; };
in
{
  inherit kernelModule;
}
