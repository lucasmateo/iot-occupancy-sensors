file='http src sensor sleep storage transmission wifi_connection'
dir='build/'

for i in $file
do
  rm -r $dir$i
done

make erase_flash
