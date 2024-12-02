Sample init scripts and service configuration for keymakerd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/keymakerd.service:    systemd service unit configuration
    contrib/init/keymakerd.openrc:     OpenRC compatible SysV style init script
    contrib/init/keymakerd.openrcconf: OpenRC conf.d file
    contrib/init/keymakerd.conf:       Upstart service configuration file
    contrib/init/keymakerd.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "keymakercore" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes keymakerd will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, keymakerd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, keymakerd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that keymakerd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If keymakerd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running keymakerd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/keymaker.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/keymakerd`  
Configuration file:  `/etc/keymakercore/keymaker.conf`  
Data directory:      `/var/lib/keymakerd`  
PID file:            `/var/run/keymakerd/keymakerd.pid` (OpenRC and Upstart) or `/var/lib/keymakerd/keymakerd.pid` (systemd)  
Lock file:           `/var/lock/subsys/keymakerd` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the keymakercore user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
keymakercore user and group.  Access to keymaker-cli and other keymakerd rpc clients
can then be controlled by group membership.

### Mac OS X

Binary:              `/usr/local/bin/keymakerd`  
Configuration file:  `~/Library/Application Support/KeymakerCore/keymaker.conf`  
Data directory:      `~/Library/Application Support/KeymakerCore`
Lock file:           `~/Library/Application Support/KeymakerCore/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start keymakerd` and to enable for system startup run
`systemctl enable keymakerd`

### OpenRC

Rename keymakerd.openrc to keymakerd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/keymakerd start` and configure it to run on startup with
`rc-update add keymakerd`

### Upstart (for Debian/Ubuntu based distributions)

Drop keymakerd.conf in /etc/init.  Test by running `service keymakerd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy keymakerd.init to /etc/init.d/keymakerd. Test by running `service keymakerd start`.

Using this script, you can adjust the path and flags to the keymakerd program by
setting the KEYMAKERD and FLAGS environment variables in the file
/etc/sysconfig/keymakerd. You can also use the DAEMONOPTS environment variable here.

### Mac OS X

Copy org.keymaker.keymakerd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.keymaker.keymakerd.plist`.

This Launch Agent will cause keymakerd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run keymakerd as the current user.
You will need to modify org.keymaker.keymakerd.plist if you intend to use it as a
Launch Daemon with a dedicated keymakercore user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
