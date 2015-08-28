#!/sbin/sh

model=`cat /proc/cmdline | sed 's/.*model.name=\([^ ]*\).*/\1/'`

rm /system/usr/keylayout/Generic.kl

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D410hn" ]; then
	cp /system/usr/keylayout/Generic-D410.kl /system/usr/keylayout/Generic.kl
else
	cp /system/usr/keylayout/Generic-D4x5.kl /system/usr/keylayout/Generic.kl
fi

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D405" ] || [ "$model" = "LG-D415" ]; then
	chmod 000 /system/etc/permissions/android.hardware.nfc.xml
	chmod 000 /system/etc/permissions/android.hardware.nfc.hce.xml
	chmod 000 /system/lib/hw/nfc_nci.pn54x.default.so
	chmod 000 /system/app/NfcNci/NfcNci.apk
fi

if [ "$model" = "LG-D415" ]; then
	chmod 000 /system/bin/fm_qsoc_patches
	chmod 000 /system/etc/permissions/qcom.fmradio.xml
	chmod 000 /system/app/FM2/FM2.apk
fi
