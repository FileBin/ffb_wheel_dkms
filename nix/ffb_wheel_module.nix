# Derivation for the out-of-tree build of the Linux driver.

{ lib
, nix-gitignore
, stdenv

, kernel  # The Linux kernel Nix package for which this module is compiled.
}:

stdenv.mkDerivation {
  pname = "ffb-wheel-driver";
  version = "0.0.0-dev";

  src = nix-gitignore.gitignoreSource [ ] ../src;

  nativeBuildInputs = kernel.moduleBuildDependencies;

  passthru = {
    # The kernel used to build the attribute.
    kernel-version = kernel.version;
  };

  makeFlags = kernel.makeFlags ++ [
    # Variable refers to the local Makefile.
    "KERNELDIR=${kernel.dev}/lib/modules/${kernel.modDirVersion}/build"
    # Variable of the Linux src tree's main Makefile.
    "INSTALL_MOD_PATH=$(out)"
  ];

  buildFlags = [ "modules" ];
  installTargets = [ "modules_install" ];

  meta = with lib; {
    description = "A Linux Driver for custom PID devices with force feedback";
    license = "GPL";
    platforms = platforms.linux;
  };
}
