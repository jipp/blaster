Import("env")

env.Replace(FUSESCMD="avrdude $UPLOADERFLAGS -e -Uefuse:w:0xff:m -Uhfuse:w:0xdf:m -Ulfuse:w:0xf1:m")
