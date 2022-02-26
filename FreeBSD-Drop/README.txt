Rust and VSCode on FreeBSD 13.0

FreeBSD is a great OS for server applications, but it is also a powerful development environment, given that Clang C/C++ tools, analysis ,extensible framework and so on.  However, FreeBSD is a great environment for rust development as well.

The following steps demonstrate how to install a desktop environment (xfce4) onto FreeBSD for the Rust Language development using the VSCode IDE.  Optional steps are covered as well that show how to remotely using SSH including accessing a desktop session from Windows OS using the Remote Desktop Connection to start.  

Required:  
1.) Basic FreeBSD installation, be sure to enable SSH, choose csh or tcsh as shell.  
2.) Editor (VI is default, you might install VIM)
3.) That you understand basic FreeBSD concepts such as login in as normal user vs root or superuser.

The following steps were verified on a 2011 Dell XPS 8300, i7-2700 8 thread, 12 G memory, running FreeBSD using the ZFS filesystem.

To install vim, login as root:
>pkg install vim

Section 1: To install a desktop system (xfce4 because it works well with remote desktop).
1.) log in or su to root.
>pkg install xorg

2.) Run the following command as root, replace "user" with your normal user account(s):
>pw groupmod video -m user || pw groupmod wheel -m user

3.) as root, install xcfe4 (note that the FreeBSD package is named "xfce" without the "4").
>pkg install xfce

4.) IMPORTANT: logout as root, to normal user, user specifed in step 2.  Then run:
>echo "exec /usr/local/bin/startxfce4 --with-ck-launch" > ~/.xinitrc

5.) On the target machine (the machine you are setting up), start the desktop AS NORMAL USER:
>startx

Make sure the desktop loads successfully before proceeding.

If you are not interested in Remote Desktop access, you can skip the following sections, just proceed to Section 4.

Section 2: To setup remote desktop accessible from Windows OS Remote Desktop Connection:
1.)  log in or su to root
>pkg install xrdp

2.) As root, add the following lines to /etc/rc.conf
xrdp_enable=”YES”
xrdp_sesman_enable=”YES”

3.) As root, open /usr/local/etc/xrdp/startwm.sh into an editor.
Comment out “exec xterm”, uncomment “exec startxfce4”

4.) As root reboot
>reboot

Section 3: Accessing the machine you just setup from Windows:
1.) Open the "Remote Desktop App"
2.) Enter the IP address of the FreeBSD machine in the Computer name field.  
3.) Enter the user name as the normal user you specified in Section 1: Step 2.
4.) Click "Show Options"  Dual monitors is supported, you can specify where to have the host or target machine play sounds and print etc.
5.) Connection, expect to be prompted for password, enter the password for the normal user you specified in Section 1: Step 2.

It may take a little time for the desktop to load the first time.

Section 4:  Install tools
1.) To use an important rust feature, you need a browser, as root run:
>pkg install firefox

2.) To read pdf files, as root, install xpdf
>pkg install xpdf

3.) DO NOT INSTALL the rust pkg that comes with FreeBSD.  Instead run the following as NORMAL USER (note if you don't want the latest nightly build, remove "| sh -s -- --default-toolchain nightly" from the command.  
Otherwise:
>curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- --default-toolchain nightly

4.) as normal user, add the following line to your ~/.cshrc
set path = ($path $HOME/.cargo/bin)

5.) in your normal user $HOME directory or subdirectory, add a rust_proj directory.
>mkdir rust_proj

6.) cd into rust_proj, then as normal user, run:
>cargo init

This will create a skeleton rust project

7.) As root, install VSCode
> pkg install vscode

8.) As normal user, cd into the rust_proj directory and run:
>vscode .

This will launch vscode into that directory as the working folder.

9.) In VSCode do: 
Ctrl + Shift + X 
This will bring up the extensions view for VSCode.  In the "Search Extensions" type in "rust-lang.rust".
This will bring up the "Rust for Visual Studio" extension in the results.  Install it.

You should be good.

Watch the video:
https://www.youtube.com/channel/UCIM-fR9HF7OgZG8tvvTz6Tg





