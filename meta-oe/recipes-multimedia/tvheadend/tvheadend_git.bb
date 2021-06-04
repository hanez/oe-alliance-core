SUMMARY = "Tvheadend: TV streaming server and recorder"
HOMEPAGE = "https://tvheadend.org/"

inherit autotools-brokensep gettext gitpkgv pkgconfig

DEPENDS = "avahi cmake-native dvb-apps libdvbcsa libpcre2 openssl uriparser zlib"

LICENSE = "GPLv3+"
LIC_FILES_CHKSUM = "file://LICENSE.md;md5=9cae5acac2e9ee2fc3aec01ac88ce5db"

SRC_URI = "git://github.com/tvheadend/tvheadend.git \
           file://0001-adjust-for-64bit-time_t.patch \
           "

SRCREV = "52b255940f9eb71904b9ac01c733cad090cd061a"
PV = "4.3+git${SRCPV}"
PKGV = "4.3+git${GITPKGV}"

S = "${WORKDIR}/git"

EXTRA_OECONF += "--arch=${TARGET_ARCH} \
                 --disable-hdhomerun_static \
                 --disable-ffmpeg_static \
                 --disable-libav \
                 "

CLEANBROKEN = "1"
