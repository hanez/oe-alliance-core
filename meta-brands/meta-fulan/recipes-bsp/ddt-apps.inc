HOMEPAGE = "https://github/Duckbox-Developers/apps"
SECTION = "base"
require conf/license/license-gplv2.inc
DEPENDS = "fulan-dvb-modules-${MACHINE}"

inherit autotools gitpkgv

SRCREV = "${AUTOREV}"
PV = "1.0+git${SRCPV}"
PKGV = "1.0+git${GITPKGV}"

SRC_URI = " \
    git://github.com/Duckbox-Developers/apps.git;protocol=https \
"

S = "${WORKDIR}/git/tools/${@d.getVar('PN',1).replace('-', '_')}"

EXTRA_OECONF = "--enable-silent-rules --prefix="
LDFLAGS += "-lpthread -lrt"
EXTRA_OEMAKE = " DRIVER_TOPDIR=${STAGING_KERNEL_DIR}"
CFLAGS:append = " -I${STAGING_KERNEL_DIR}/multicom/include"

do_configure:prepend() {
    touch ${S}/NEWS
    touch ${S}/README
    touch ${S}/AUTHORS
    touch ${S}/COPYING
    touch ${S}/ChangeLog
}
