find . -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" > cscope.files
cscope -q -R -b -i cscope.files
ctags -e -R .

# ycm
#ctags --fields=+l $(find . -name '*.[ch]' -print)
ln -sf TAGS .tags
