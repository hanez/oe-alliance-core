SUMMARY = "Hardware drivers for Dreambox"
SECTION = "base"
LICENSE = "CLOSED"
PRIORITY = "required"
INC_PR = "r0"
require conf/license/license-close.inc

DREAMBOX_DVB_MODULES_MIRROR ?= "http://dreamboxupdate.com/download/opendreambox/2.5.0/dreambox-dvb-modules/${KV}-${MACHINE}-${DRIVERDATE}/${MACHINE}/${MD5SUM}"

SRC_URI = "${DREAMBOX_DVB_MODULES_MIRROR}/dreambox-dvb-modules_${KV}-${MACHINE}-${DRIVERDATE}_${MACHINE}.tar.xz;name=${MACHINE}"

S = "${WORKDIR}/dreambox-dvb-modules_${KV}-${MACHINE}-${DRIVERDATE}_${MACHINE}"

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"

INSANE_SKIP:${PN}:append = " already-stripped"

do_install() {
    find . -depth -not -path "./patches*" -not -path "./.pc*" -print0 | cpio --null -pdlu ${D}
    chown -hR root:root ${D}
}

do_install:append() {
    install -d ${D}${sysconfdir}/modules-load.d
    echo stb-core > ${D}${sysconfdir}/modules-load.d/01-${BPN}-stb-core.conf
    chmod 0644 ${D}${sysconfdir}/modules-load.d/01-${BPN}-stb-core.conf
    if [ -f ${D}/lib/modules/${DM_LOCALVERSION}/extra/lcd.ko ]; then
        echo lcd > ${D}${sysconfdir}/modules-load.d/02-${BPN}-lcd.conf
        chmod 0644 ${D}${sysconfdir}/modules-load.d/02-${BPN}-lcd.conf
    fi
    for module in bcm7435 dreambox_keyboard ble; do
        if [ -f ${D}/lib/modules/${DM_LOCALVERSION}/extra/$module.ko ]; then
            echo $module >> ${D}${sysconfdir}/modules-load.d/10-${BPN}.conf
        fi
    done
    chmod 0644 ${D}${sysconfdir}/modules-load.d/10-${BPN}.conf
}

PACKAGES =+ "${PN}-lcd ${PN}-stb-core"

RDEPENDS:${PN} = "dreambox-secondstage-${MACHINE} kernel-${DM_LOCALVERSION} ${PN}-stb-core"
RDEPENDS:${PN}-lcd = "${PN}-stb-core"
RRECOMMENDS:${PN} = "${PN}-lcd"

FILES:${PN} = "${sysconfdir}/modules-load.d/10-${BPN}.conf \
               /lib/modules/${DM_LOCALVERSION}/extra/"

FILES:${PN}-lcd = "${sysconfdir}/modules-load.d/02-${BPN}-lcd.conf \
                   /lib/modules/${DM_LOCALVERSION}/extra/lcd.ko"

FILES:${PN}-stb-core = "${sysconfdir}/modules-load.d/01-${BPN}-stb-core.conf \
                        /lib/modules/${DM_LOCALVERSION}/extra/stb-core.ko"

# We don't use KERNEL_VERSION in this recipe, because the
# precompiled modules depend on a specific version.
DM_LOCALVERSION = "${@'-'.join('${PV}'.split('-')[:-1])}-${MACHINE}"
DRIVERDATE = "${@'${PV}'.split('-')[-1]}"
MD5SUM = "${@d.getVarFlag('SRC_URI', 'dm7080.md5sum', True)}"

pkg_postinst:${PN} () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
pkg_postinst:${PN}-lcd () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
pkg_postinst:${PN}-stb-core () {
if [ -z "$D" ]; then
	depmod -a ${DM_LOCALVERSION}
fi
}
