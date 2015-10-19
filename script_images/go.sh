echo "#define NBRIMG `ls -1 | wc -l`"
echo "const unsigned char images[$((`ls -1 | wc -l`*48))] PROGMEM = {"
for i in *.txt
do
  echo "// $i"; cat $i | egrep -v "^#" |   sed "s/.*srgb(//;s/)/,/"
  echo -e ""
done
echo "};"
