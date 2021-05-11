---
layout: post
title: "tracker-miner-fs"
date: 2021-04-30 16:23:10 -0400
relatives: tracker-miner-fs
categories: [linux]
---

Have some patience. It eventually will go over.
Tracker is an indexing system. It searches all files for words, which are included in a database so you can quickly find files containing specific words.

If, despite your patience, tracker keeps using high cpu, then there may be an issue with the database. In that case, clearing the database and having tracker reconstruct it may help:
```
tracker reset --hard ; tracker daemon --start
``` 

## Disable Tracker

To avoid the period of high processor use after login, you may want to disable Tracker. 

This will disable full text search and renaming of mediafiles based on tags. It will disable the "Starred files" feature (Ubuntu 20.04). However, file name search in Files will continue to work. In the overview, it appears as if only recent files are found after disabling Tracker.

Run the following command to disable tracker for the current user:
```
systemctl --user mask tracker-store.service tracker-miner-fs.service tracker-miner-rss.service tracker-extract.service tracker-miner-apps.service tracker-writeback.service

tracker reset --hard

sudo reboot 
```

to undo this
``` 
systemctl --user unmask tracker-store.service tracker-miner-fs.service tracker-miner-rss.service tracker-extract.service tracker-miner-apps.service tracker-writeback.service

sudo reboot
```

With following commands, you

1) stop the tracker daemon (for this session)

2) move to your local autostart directory and 

3) copy startup files for the various Tracker processes to your local autostart folder. 

In 4) you disable the autostart of these processes, and in 

5) you free the disk space taken by the cache that Tracker may already have made (could be 2 - 4 GB).

```
tracker daemon -t
cd ~/.config/autostart
cp -v /etc/xdg/autostart/tracker-* ./
for FILE in tracker-* ; do echo Hidden=true >> $FILE; done
rm -rf ~/.cache/tracker ~/.local/share/tracker
 
```

otras opciones similares
[https://www.sololinux.es/procesos-tracker-excesivo-consumo-de-cpu-y-hdd/](https://www.sololinux.es/procesos-tracker-excesivo-consumo-de-cpu-y-hdd/)