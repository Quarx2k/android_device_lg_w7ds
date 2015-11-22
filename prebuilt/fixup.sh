#!/sbin/sh

model=`cat /proc/cmdline | sed 's/.*model.name=\([^ ]*\).*/\1/'`

rm /system/usr/keylayout/Generic.kl

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D410hn" ]; then
	cp /system/usr/keylayout/Generic-D410.kl /system/usr/keylayout/Generic.kl
else
	cp /system/usr/keylayout/Generic-D4x5.kl /system/usr/keylayout/Generic.kl
fi

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D405" ] || [ "$model" = "LG-D415" ]; then
	rm /system/etc/permissions/android.hardware.nfc.xml
	rm /system/etc/permissions/android.hardware.nfc.hce.xml
	rm /system/lib/hw/nfc_nci.pn54x.default.so
	rm -rf /system/app/NfcNci/
fi

if [ "$model" = "LG-D415" ]; then
	rm /system/bin/fm_qsoc_patches
	rm /system/etc/permissions/qcom.fmradio.xml
	rm -rf /system/app/FM2/
fi
