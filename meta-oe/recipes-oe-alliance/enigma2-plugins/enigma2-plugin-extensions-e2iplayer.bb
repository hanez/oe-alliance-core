SUMMARY = "E2iPlayer"
DESCRIPTION = "Watch Videos Online"
HOMEPAGE = "https://gitlab.com/iptvplayer-for-e2/"
SECTION = "multimedia"
LICENSE = "GPLv2"
require conf/license/license-gplv2.inc
require conf/python/python3-compileall.inc

SRC_URI = "git://github.com/oe-mirrors/e2iplayer.git;protocol=http;branch=python3"

S = "${WORKDIR}/git"

inherit gitpkgv
SRCREV = "${AUTOREV}"
PV = "git${SRCPV}"
PKGV = "git${GITPKGV}"
PR = "r0"

inherit ${@bb.utils.contains("PYTHON_PN", "python", "distutils-openplugins", "distutils3-openplugins", d)} gettext

DEPENDS = "gettext-native ${PYTHON_PN}-future-native ${PYTHON_PN}"
RRECOMMENDS:${PN} = " \
        enigma2-plugin-extensions-e2iplayer-deps \
        ${PYTHON_PN}-compression \
        ${PYTHON_PN}-core \
        ${PYTHON_PN}-html \
        ${PYTHON_PN}-e2icjson \
        ${PYTHON_PN}-json \
        ${PYTHON_PN}-shell \
        ${@bb.utils.contains("PYTHON_PN", "python", "${PYTHON_PN}-subprocess", "", d)} \
        ${@bb.utils.contains("PYTHON_PN", "python", "${PYTHON_PN}-textutils", "", d)} \
        "

RDEPENDS:{PN}-src = "${PN}"
FILES:${PN}-src = " \
        ${libdir}/enigma2/python/Plugins/*/*.py \
        ${libdir}/enigma2/python/Plugins/*/*/*.py \
        ${libdir}/enigma2/python/Plugins/*/*/*/*.py \
        ${libdir}/enigma2/python/Plugins/*/*/*/*/*.py \
        ${libdir}/enigma2/python/Plugins/*/*/*/*/*/*.py \
        ${libdir}/enigma2/python/Plugins/*-py2.7.egg-info/* \
        ${libdir}/enigma2/python/Plugins/*/locale/*/LC_MESSAGES/*.po \
        "
deltask package_qa
