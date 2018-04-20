lflags=`pkg-config --libs gtk+-3.0`
cflags=`pkg-config --cflags gtk+-3.0`
gcc gtk_leaks.c -o gtk_leaks $lflags $cflags
