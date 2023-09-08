# MDDEV

This project is a loosely organized accumulation of code from years of interfacing with medical devices for
data collection as well as code for visualization and analysis.  It mostly requires JDK7 and many dependencies
are still valid and functional though possibly outdated by their peers.  For the most part, this code was
unmanaged from 2018 to 2023.  Since then I have taken a more active interest in seeing the code returned to
a state that can be useful to others.

This code was developed by a single developer: me.  I'm open to contributions, though at this point in time
you may have more luck forking out some small component.  

This project is not currently easy to build.  Some parts of this code depend on an existing installation of 
"R" together with JavaGD and rJava.  Also the GUI is based on Swing and JFormdesigner.  JFormDesigner is not
necessary to build and run this project, but if you intend to make changes, it is highly recommended.

We also use HDF5 as the primary data storage engine, with some support for XLS and other formats.  HDF5 is probably
required to store waveforms from medical devices.

Major components include 
* "idea" -- basic infrastrusture and medical device interfaces (Java)
* "pista" -- an alternative library for interfaces to medical devices written in C, can be used by the Java library
* "dm" -- data management compoents
* "icuvisdaq" -- a UI for data collection and online analysis
* "tsoffline" -- for offline analysis and visualization

## Prerequisites and External Tools

* HDF5
* R with JavaGD and rJava packages
* (Optional) JFormDesigner
* (Optional) Launch4J

## Getting started

Add the following to the JVM path: 
```
-Djava.library.path=/usr/lib64:/usr/lib64/hdf5
```

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## Project status


