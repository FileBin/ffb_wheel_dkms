with (import <nixpkgs> {  });
mkShell {
    packages = [
        gcc
        linux
        linuxHeaders
        glibc_multi
        clang-tools
        ncurses
        bear
        gh
        gnumake
        (vscode-with-extensions.override {
            vscodeExtensions = with vscode-extensions; [
                llvm-vs-code-extensions.vscode-clangd
                ms-vscode.cpptools
                twxs.cmake
                ms-vscode.cmake-tools
                ms-vscode.hexeditor
                tal7aouy.icons
                jnoortheen.nix-ide
                wmaurer.change-case
            ];
        })
    ];
}
