#!/system/bin/sh
setprop gsm.version.baseband `strings /firmware/image/modem.b21 | grep "^M8626A-" | head -1`
