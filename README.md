# gsh
Simple Shell.

for using as default shell :

root# cp gsh /bin/gsh

root# echo "/bin/gsh" >> /etc/shells

then change your default shell by editing /etc/passwd file or using chsh command:

chsh -s /bin/gsh
