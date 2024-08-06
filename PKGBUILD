# Author: RickaPrincy <rckprincy@gmail.com>
pkgname=sdlk
pkgver=0.0.1
pkgrel=1
pkgdesc="SDL2 Kit (SDL2 Wrapper)"
arch=('x86_64')
depends=('sdl2' 'sdl2_image' 'sdl2_ttf')
url="https://github.com/RickaPrincy/sdlk.git"
license=('MIT')
source=("sdlk@$pkgver.tar.gz::https://github.com/RickaPrincy/sdlk.git/releases/download/v0.0.1/sdlk@$pkgver.tar.gz")

sha256sums=("SHASUM")

package() {
    echo "Installing to \"$pkgdir/usr/\""
    mkdir -p "$pkgdir/usr/include"
    mkdir -p "$pkgdir/usr/lib"
    cp -r "sdlk@$pkgver/include" "$pkgdir/usr"
    cp -r "sdlk@$pkgver/lib" "$pkgdir/usr"
}
