# qfetch - Quick Fetch

**qfetch** is a fetch program made to be pretty quick, being written in 100% C.

## Information fetched:
  - Hostname
  - Username
  - Operating System
  - Host/Hardware info
  - Kernel version
  - System uptime
  - Memory usage
  - Installed packages count

## ASCII Art
There isn't a lot of ASCII art just yet, almost all of the art is copied from [pfetch](https://github.com/dylanaraps/pfetch)

Currently Supported:
- Arch
- Arco
- Artix
- Cachyos
- Debian
- Devuan
- Gentoo
- Hyperbola
- Manjaro
- Linux Mint
- Ubuntu

## Installation
```bash
git clone https://github.com/themeaner0/qfetch.git
cd qfetch
sudo make clean install
```

## Run
```bash
qfetch
```

Options:

    -v : Show the version of qfetch.

    --distro NAME : choose custom ASCII logo.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
