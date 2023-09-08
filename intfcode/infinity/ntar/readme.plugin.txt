/** @defgroup PluginArchitecture Plugin architecture
* @{



<h4>HOW TO WRITE A BLOCK PLUGIN</h4>


A block plugin is used to save or read a specific, user defined block to a NTAR
trace file.

The philosophy behind these plugins makes use of a set of callbacks that should
be exposed. The pointers to such callbacks are then registered to the core NTAR
engine. Every plugin manages data written or read to/from a trace file in form
of buffers of bytes of known size. The plugins are not required (and must not) 
access the underlying trace file descriptor directly.

Every plugin is formed by at least three files (where xxx is the identifier of
the plugin):
<table>
  <tr>
    <td>plugin_xxx.c</td><td>It contains the actual code to read and write a block.</td>
  </tr>
  <tr>
    <td>plugin_xxx.h</td><td>It contains the public structures exposed to NTAR users. This 
                 include file is automatically available when ntar.h is 
                 included in a user application.</td>
  </tr>
  <tr>
    <td>plugin_xxx_int.h</td><td>It contains all the internal definitions used by the plugin 
                 (e.g. the prototypes of the functions defined by the plugin).</td>
  </tr>
</table>


Every plugin should export the following callbacks (again xxx stands for the identifier of the plugin):<br>
\ref PluginInterface 

@}*/