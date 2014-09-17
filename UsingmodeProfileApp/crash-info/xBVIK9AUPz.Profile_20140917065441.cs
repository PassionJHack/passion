S/W Version Information
Model: Ref.Device-PQ
Tizen-Version: 2.2.1
Build-Number: Tizen_Ref.Device-PQ_20131118.1124
Build-Date: 2013.11.18 11:24:59

Crash Information
Process Name: Profile
PID: 2923
Date: 2014-09-17 06:54:41(GMT+0900)
Executable File Path: /opt/apps/xBVIK9AUPz/bin/Profile
This process is multi-thread process
pid=2923 tid=2923
Signal: 11
      (SIGSEGV)
      si_code: -6
      signal sent by tkill (sent by pid 2923, uid 5000)

Register Information
r0   = 0x00000000, r1   = 0x007c00e0
r2   = 0xedabb000, r3   = 0x0014cff0
r4   = 0xb26454c8, r5   = 0x00189400
r6   = 0x00377b20, r7   = 0x00418648
r8   = 0xbeeb4f60, r9   = 0x000b02e0
r10  = 0xb4429940, fp   = 0xbeeb4c28
ip   = 0x000033a8, sp   = 0xbeeb4b30
lr   = 0xb6ee28b5, pc   = 0xb2656190
cpsr = 0x60000010

Memory Information
MemTotal:   797320 KB
MemFree:    409804 KB
Buffers:     13900 KB
Cached:     157300 KB
VmPeak:     119424 KB
VmSize:      95524 KB
VmLck:           0 KB
VmHWM:       50664 KB
VmRSS:       38984 KB
VmData:      17636 KB
VmStk:         136 KB
VmExe:          32 KB
VmLib:       45504 KB
VmPTE:          98 KB
VmSwap:          0 KB

Maps Information
00008000 00010000 r-xp /usr/bin/launchpad_preloading_preinitializing_daemon
00018000 000dc000 rw-p [heap]
000dc000 00ae0000 rw-p [heap]
b1744000 b1749000 r-xp /usr/lib/scim-1.0/1.4.0/Config/socket.so
b203d000 b204e000 r-xp /usr/lib/scim-1.0/1.4.0/IMEngine/socket.so
b2227000 b222c000 r-xp /usr/lib/libhaptic-module.so
b2286000 b2289000 r-xp /usr/lib/bufmgr/libtbm_exynos4412.so.0.0.0
b2291000 b2292000 r-xp /usr/lib/libdrm_slp.so.1.0.0
b229a000 b22a4000 r-xp /usr/lib/evas/modules/engines/software_generic/linux-gnueabi-armv7l-1.7.99/module.so
b22d0000 b22e4000 r-xp /usr/lib/libnetwork.so.0.0.0
b22ed000 b2301000 r-xp /usr/lib/libwifi-direct.so.0.0
b2309000 b2311000 r-xp /usr/lib/libcapi-network-tethering.so.0.1.0
b2312000 b231b000 r-xp /usr/lib/libcapi-network-connection.so.0.1.3_18
b2323000 b2349000 r-xp /usr/lib/libzmq.so.3.0.0
b2353000 b235c000 r-xp /usr/lib/libpims-ipc.so.0.0.30
b2364000 b2429000 r-xp /usr/lib/osp/libosp-net.so.1.2.2.0
b2437000 b2450000 r-xp /usr/lib/libaccounts-svc.so.0.2.66
b2458000 b24ca000 r-xp /usr/lib/libcontacts-service2.so.0.9.114.7
b24e9000 b252c000 r-xp /usr/lib/libcalendar-service2.so.0.1.44
b2536000 b2553000 r-xp /usr/lib/osp/libosp-image.so.1.2.2.0
b255c000 b261d000 r-xp /usr/lib/osp/libosp-social.so.1.2.2.0
b2627000 b2630000 r-xp /usr/lib/evas/modules/engines/software_x11/linux-gnueabi-armv7l-1.7.99/module.so
b2639000 b265d000 r-xp /opt/usr/apps/xBVIK9AUPz/bin/Profile.exe
b2666000 b26d8000 r-xp /usr/lib/libosp-env-config.so.1.2.2.1
b26e0000 b271a000 r-xp /usr/lib/libpulsecommon-0.9.23.so
b2723000 b2727000 r-xp /usr/lib/libmmfsoundcommon.so.0.0.0
b272f000 b2760000 r-xp /usr/lib/libpulse.so.0.12.4
b2768000 b27cb000 r-xp /usr/lib/libasound.so.2.0.0
b27d5000 b27d8000 r-xp /usr/lib/libpulse-simple.so.0.0.3
b27e0000 b27e4000 r-xp /usr/lib/libascenario-0.2.so.0.0.0
b27ed000 b280a000 r-xp /usr/lib/libavsysaudio.so.0.0.1
b2812000 b2820000 r-xp /usr/lib/libmmfsound.so.0.1.0
b2828000 b28c4000 r-xp /usr/lib/libgstreamer-0.10.so.0.30.0
b28d0000 b2911000 r-xp /usr/lib/libgstbase-0.10.so.0.30.0
b291a000 b2923000 r-xp /usr/lib/libgstapp-0.10.so.0.25.0
b292b000 b2938000 r-xp /usr/lib/libgstinterfaces-0.10.so.0.25.0
b2941000 b2947000 r-xp /usr/lib/libUMP.so
b294f000 b2952000 r-xp /usr/lib/libmm_ta.so.0.0.0
b295a000 b2969000 r-xp /usr/lib/libICE.so.6.3.0
b2973000 b2978000 r-xp /usr/lib/libSM.so.6.0.1
b2980000 b2981000 r-xp /usr/lib/libmmfkeysound.so.0.0.0
b2989000 b2991000 r-xp /usr/lib/libmmfcommon.so.0.0.0
b2999000 b29a1000 r-xp /usr/lib/libaudio-session-mgr.so.0.0.0
b29ac000 b29af000 r-xp /usr/lib/libmmfsession.so.0.0.0
b29b7000 b29fb000 r-xp /usr/lib/libmmfplayer.so.0.0.0
b2a04000 b2a17000 r-xp /usr/lib/libEGL_platform.so
b2a20000 b2af7000 r-xp /usr/lib/libMali.so
b2b02000 b2b08000 r-xp /usr/lib/libxcb-render.so.0.0.0
b2b10000 b2b11000 r-xp /usr/lib/libxcb-shm.so.0.0.0
b2b1a000 b2b58000 r-xp /usr/lib/libGLESv2.so.2.0
b2b60000 b2bab000 r-xp /usr/lib/libtiff.so.5.1.0
b2bb6000 b2bdf000 r-xp /usr/lib/libturbojpeg.so
b2bf8000 b2bfe000 r-xp /usr/lib/libmmutil_imgp.so.0.0.0
b2c06000 b2c0c000 r-xp /usr/lib/libgif.so.4.1.6
b2c14000 b2c36000 r-xp /usr/lib/libavutil.so.51.73.101
b2c45000 b2c73000 r-xp /usr/lib/libswscale.so.2.1.101
b2c7c000 b2f73000 r-xp /usr/lib/libavcodec.so.54.59.100
b329a000 b32b3000 r-xp /usr/lib/libpng12.so.0.50.0
b32bc000 b32c2000 r-xp /usr/lib/libfeedback.so.0.1.4
b32ca000 b32d6000 r-xp /usr/lib/libtts.so
b32de000 b32f5000 r-xp /usr/lib/libEGL.so.1.4
b32fe000 b33b5000 r-xp /usr/lib/libcairo.so.2.11200.12
b33bf000 b33d9000 r-xp /usr/lib/osp/libosp-image-core.so.1.2.2.0
b33e2000 b3cdd000 r-xp /usr/lib/osp/libosp-uifw.so.1.2.2.1
b3d50000 b3d55000 r-xp /usr/lib/libslp_devman_plugin.so
b3d5e000 b3d61000 r-xp /usr/lib/libsyspopup_caller.so.0.1.0
b3d69000 b3d6d000 r-xp /usr/lib/libsysman.so.0.2.0
b3d75000 b3d86000 r-xp /usr/lib/libsecurity-server-commons.so.1.0.0
b3d8f000 b3d91000 r-xp /usr/lib/libsystemd-daemon.so.0.0.1
b3d99000 b3d9b000 r-xp /usr/lib/libdeviced.so.0.1.0
b3da3000 b3db9000 r-xp /usr/lib/libpkgmgr_parser.so.0.1.0
b3dc1000 b3dc3000 r-xp /usr/lib/libpkgmgr_installer_status_broadcast_server.so.0.1.0
b3dcb000 b3dce000 r-xp /usr/lib/libpkgmgr_installer_client.so.0.1.0
b3dd6000 b3dd9000 r-xp /usr/lib/libdevice-node.so.0.1
b3de1000 b3de5000 r-xp /usr/lib/libheynoti.so.0.0.2
b3ded000 b3e32000 r-xp /usr/lib/libsoup-2.4.so.1.5.0
b3e3b000 b3e50000 r-xp /usr/lib/libsecurity-server-client.so.1.0.1
b3e59000 b3e5d000 r-xp /usr/lib/libcapi-system-info.so.0.2.0
b3e65000 b3e6a000 r-xp /usr/lib/libcapi-system-system-settings.so.0.0.2
b3e72000 b3e73000 r-xp /usr/lib/libcapi-system-power.so.0.1.1
b3e7c000 b3e7f000 r-xp /usr/lib/libcapi-system-device.so.0.1.0
b3e87000 b3e8a000 r-xp /usr/lib/libcapi-system-runtime-info.so.0.0.3
b3e93000 b3e96000 r-xp /usr/lib/libcapi-network-serial.so.0.0.8
b3e9e000 b3e9f000 r-xp /usr/lib/libcapi-content-mime-type.so.0.0.2
b3ea7000 b3eb5000 r-xp /usr/lib/libcapi-appfw-application.so.0.1.0
b3ebe000 b3ee0000 r-xp /usr/lib/libSLP-tapi.so.0.0.0
b3ee8000 b3eeb000 r-xp /usr/lib/libuuid.so.1.3.0
b3ef4000 b3f12000 r-xp /usr/lib/libpkgmgr-info.so.0.0.17
b3f1a000 b3f31000 r-xp /usr/lib/libpkgmgr-client.so.0.1.68
b3f3a000 b3f3b000 r-xp /usr/lib/libpmapi.so.1.2
b3f43000 b3f4b000 r-xp /usr/lib/libminizip.so.1.0.0
b3f53000 b3f5e000 r-xp /usr/lib/libmessage-port.so.1.2.2.1
b3f66000 b403e000 r-xp /usr/lib/libxml2.so.2.7.8
b404b000 b4069000 r-xp /usr/lib/libpcre.so.0.0.1
b4071000 b4074000 r-xp /usr/lib/libiniparser.so.0
b407d000 b4081000 r-xp /usr/lib/libhaptic.so.0.1
b4089000 b4094000 r-xp /usr/lib/libcryptsvc.so.0.0.1
b40a1000 b40a6000 r-xp /usr/lib/libdevman.so.0.1
b40af000 b40b3000 r-xp /usr/lib/libchromium.so.1.0
b40bb000 b40c1000 r-xp /usr/lib/libappsvc.so.0.1.0
b40c9000 b40ca000 r-xp /usr/lib/osp/libappinfo.so.1.2.2.1
b40da000 b40dc000 r-xp /opt/usr/apps/xBVIK9AUPz/bin/Profile
b40e4000 b40ea000 r-xp /usr/lib/libalarm.so.0.0.0
b40f3000 b4105000 r-xp /usr/lib/libprivacy-manager-client.so.0.0.5
b410d000 b440c000 r-xp /usr/lib/osp/libosp-appfw.so.1.2.2.1
b4433000 b443d000 r-xp /lib/libnss_files-2.13.so
b4446000 b444f000 r-xp /lib/libnss_nis-2.13.so
b4458000 b4469000 r-xp /lib/libnsl-2.13.so
b4474000 b447a000 r-xp /lib/libnss_compat-2.13.so
b4483000 b448c000 r-xp /usr/lib/libcapi-security-privilege-manager.so.0.0.3
b47b4000 b47c5000 r-xp /usr/lib/libcom-core.so.0.0.1
b47cd000 b47cf000 r-xp /usr/lib/libdri2.so.0.0.0
b47d7000 b47df000 r-xp /usr/lib/libdrm.so.2.4.0
b47e7000 b47eb000 r-xp /usr/lib/libtbm.so.1.0.0
b47f3000 b47f6000 r-xp /usr/lib/libXv.so.1.0.0
b47fe000 b48c9000 r-xp /usr/lib/libscim-1.0.so.8.2.3
b48df000 b48ef000 r-xp /usr/lib/libnotification.so.0.1.0
b48f7000 b491b000 r-xp /usr/lib/ecore/immodules/libisf-imf-module.so
b4924000 b4934000 r-xp /lib/libresolv-2.13.so
b4938000 b493a000 r-xp /usr/lib/libgmodule-2.0.so.0.3200.3
b4942000 b4a95000 r-xp /usr/lib/libcrypto.so.1.0.0
b4ab3000 b4aff000 r-xp /usr/lib/libssl.so.1.0.0
b4b0b000 b4b37000 r-xp /usr/lib/libidn.so.11.5.44
b4b40000 b4b4a000 r-xp /usr/lib/libcares.so.2.0.0
b4b52000 b4b69000 r-xp /lib/libexpat.so.1.5.2
b4b73000 b4b97000 r-xp /usr/lib/libicule.so.48.1
b4ba0000 b4ba8000 r-xp /usr/lib/libsf_common.so
b4bb0000 b4c4b000 r-xp /usr/lib/libstdc++.so.6.0.14
b4c5e000 b4d3b000 r-xp /usr/lib/libgio-2.0.so.0.3200.3
b4d46000 b4d6b000 r-xp /usr/lib/libexif.so.12.3.3
b4d7f000 b4d89000 r-xp /usr/lib/libethumb.so.1.7.99
b4d91000 b4dd5000 r-xp /usr/lib/libsndfile.so.1.0.25
b4de3000 b4de5000 r-xp /usr/lib/libctxdata.so.0.0.0
b4ded000 b4dfb000 r-xp /usr/lib/libremix.so.0.0.0
b4e03000 b4e04000 r-xp /usr/lib/libecore_imf_evas.so.1.7.99
b4e0c000 b4e25000 r-xp /usr/lib/liblua-5.1.so
b4e2e000 b4e35000 r-xp /usr/lib/libembryo.so.1.7.99
b4e3e000 b4e41000 r-xp /usr/lib/libecore_input_evas.so.1.7.99
b4e49000 b4e86000 r-xp /usr/lib/libcurl.so.4.3.0
b4e90000 b4e94000 r-xp /usr/lib/libecore_ipc.so.1.7.99
b4e9d000 b4f07000 r-xp /usr/lib/libpixman-1.so.0.28.2
b4f14000 b4f38000 r-xp /usr/lib/libfontconfig.so.1.5.0
b4f41000 b4f9d000 r-xp /usr/lib/libharfbuzz.so.0.907.0
b4faf000 b4fc3000 r-xp /usr/lib/libfribidi.so.0.3.1
b4fcb000 b5020000 r-xp /usr/lib/libfreetype.so.6.8.1
b502b000 b504f000 r-xp /usr/lib/libjpeg.so.8.0.2
b5067000 b507e000 r-xp /lib/libz.so.1.2.5
b5086000 b5093000 r-xp /usr/lib/libsensor.so.1.1.0
b509e000 b50a0000 r-xp /usr/lib/libapp-checker.so.0.1.0
b50a8000 b50ae000 r-xp /usr/lib/libxdgmime.so.1.1.0
b61c5000 b62ad000 r-xp /usr/lib/libicuuc.so.48.1
b62ba000 b63da000 r-xp /usr/lib/libicui18n.so.48.1
b63e8000 b63eb000 r-xp /usr/lib/libSLP-db-util.so.0.1.0
b63f3000 b63fc000 r-xp /usr/lib/libvconf.so.0.2.45
b6404000 b6412000 r-xp /usr/lib/libail.so.0.1.0
b641a000 b6432000 r-xp /usr/lib/libdbus-glib-1.so.2.2.2
b6433000 b6438000 r-xp /usr/lib/libffi.so.5.0.10
b6440000 b6441000 r-xp /usr/lib/libgthread-2.0.so.0.3200.3
b6449000 b6453000 r-xp /usr/lib/libXext.so.6.4.0
b645c000 b645f000 r-xp /usr/lib/libXtst.so.6.1.0
b6467000 b646d000 r-xp /usr/lib/libXrender.so.1.3.0
b6475000 b647b000 r-xp /usr/lib/libXrandr.so.2.2.0
b6483000 b6484000 r-xp /usr/lib/libXinerama.so.1.0.0
b648d000 b6496000 r-xp /usr/lib/libXi.so.6.1.0
b649e000 b64a1000 r-xp /usr/lib/libXfixes.so.3.1.0
b64a9000 b64ab000 r-xp /usr/lib/libXgesture.so.7.0.0
b64b3000 b64b5000 r-xp /usr/lib/libXcomposite.so.1.0.0
b64bd000 b64be000 r-xp /usr/lib/libXdamage.so.1.1.0
b64c7000 b64ce000 r-xp /usr/lib/libXcursor.so.1.0.2
b64d6000 b64de000 r-xp /usr/lib/libemotion.so.1.7.99
b64e6000 b6501000 r-xp /usr/lib/libecore_con.so.1.7.99
b650a000 b650f000 r-xp /usr/lib/libecore_imf.so.1.7.99
b6518000 b6520000 r-xp /usr/lib/libethumb_client.so.1.7.99
b6528000 b652a000 r-xp /usr/lib/libefreet_trash.so.1.7.99
b6532000 b6536000 r-xp /usr/lib/libefreet_mime.so.1.7.99
b653f000 b6555000 r-xp /usr/lib/libefreet.so.1.7.99
b655f000 b6568000 r-xp /usr/lib/libedbus.so.1.7.99
b6570000 b6575000 r-xp /usr/lib/libecore_fb.so.1.7.99
b657e000 b65da000 r-xp /usr/lib/libedje.so.1.7.99
b65e4000 b65fb000 r-xp /usr/lib/libecore_input.so.1.7.99
b6616000 b661b000 r-xp /usr/lib/libecore_file.so.1.7.99
b6623000 b6640000 r-xp /usr/lib/libecore_evas.so.1.7.99
b6649000 b6688000 r-xp /usr/lib/libeina.so.1.7.99
b6691000 b6740000 r-xp /usr/lib/libevas.so.1.7.99
b6762000 b6775000 r-xp /usr/lib/libeet.so.1.7.99
b677e000 b67e8000 r-xp /lib/libm-2.13.so
b67f4000 b67fb000 r-xp /usr/lib/libutilX.so.1.1.0
b6803000 b6808000 r-xp /usr/lib/libappcore-common.so.1.1
b6810000 b681b000 r-xp /usr/lib/libaul.so.0.1.0
b6824000 b6858000 r-xp /usr/lib/libgobject-2.0.so.0.3200.3
b6861000 b6891000 r-xp /usr/lib/libecore_x.so.1.7.99
b689a000 b68af000 r-xp /usr/lib/libecore.so.1.7.99
b68c6000 b69e6000 r-xp /usr/lib/libelementary.so.1.7.99
b69f9000 b69fc000 r-xp /lib/libattr.so.1.1.0
b6a04000 b6a06000 r-xp /usr/lib/libXau.so.6.0.0
b6a0e000 b6a14000 r-xp /lib/librt-2.13.so
b6a1d000 b6a25000 r-xp /lib/libcrypt-2.13.so
b6a55000 b6a58000 r-xp /lib/libcap.so.2.21
b6a60000 b6a62000 r-xp /usr/lib/libiri.so
b6a6a000 b6a7f000 r-xp /usr/lib/libxcb.so.1.1.0
b6a87000 b6a92000 r-xp /lib/libunwind.so.8.0.1
b6ac0000 b6bdd000 r-xp /lib/libc-2.13.so
b6beb000 b6bf4000 r-xp /lib/libgcc_s-4.5.3.so.1
b6bfc000 b6bff000 r-xp /usr/lib/libsmack.so.1.0.0
b6c07000 b6c33000 r-xp /usr/lib/libdbus-1.so.3.7.2
b6c3c000 b6c40000 r-xp /usr/lib/libbundle.so.0.1.22
b6c48000 b6c4a000 r-xp /lib/libdl-2.13.so
b6c53000 b6d2d000 r-xp /usr/lib/libglib-2.0.so.0.3200.3
b6d36000 b6da0000 r-xp /usr/lib/libsqlite3.so.0.8.6
b6daa000 b6db7000 r-xp /usr/lib/libprivilege-control.so.0.0.2
b6dc0000 b6ea6000 r-xp /usr/lib/libX11.so.6.3.0
b6eb1000 b6ec5000 r-xp /lib/libpthread-2.13.so
b6ed5000 b6ed9000 r-xp /usr/lib/libappcore-efl.so.1.1
b6ee2000 b6ee3000 r-xp /usr/lib/libdlog.so.0.0.0
b6eeb000 b6eef000 r-xp /usr/lib/libsys-assert.so
b6ef7000 b6f14000 r-xp /lib/ld-2.13.so
bee96000 beeb7000 rwxp [stack]
End of Maps Information

Callstack Information (PID:2923)
Call Stack Count: 40
 0: ProfileListForm::SaveUsingmodeProfile(Tizen::Base::String, Tizen::Base::String) + 0x168 (0xb2656190) [/opt/apps/xBVIK9AUPz/bin/Profile.exe] + 0x1d190
 1: CreateProfileForm::OnActionPerformed(Tizen::Ui::Control const&, int) + 0x408 (0xb26453bc) [/opt/apps/xBVIK9AUPz/bin/Profile.exe] + 0xc3bc
 2: non-virtual thunk to CreateProfileForm::OnActionPerformed(Tizen::Ui::Control const&, int) + 0x3c (0xb2645504) [/opt/apps/xBVIK9AUPz/bin/Profile.exe] + 0xc504
End of Call Stack

Package Information
Package Name: xBVIK9AUPz.Profile
Package ID : xBVIK9AUPz
Version: 1.0.0
Package Type: tpk
App Name: 사용자 프로파일
App ID: xBVIK9AUPz.Profile
Type: Application
Categories: (NULL)
