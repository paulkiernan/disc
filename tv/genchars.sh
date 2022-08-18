CHARMAP=$(cat charmap.txt)

echo $CHARMAP

convert \
  -size 20x1300 xc:none \
  -font "Press-Start-2P" \
  -pointsize 20 \
  -interline-spacing 0 \
  -fill grey \
  -gravity North \
  -annotate +4+20 "$CHARMAP" font.png
