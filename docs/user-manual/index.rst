.. _um:

User manual
===========

LwWDG library is very simple and easy to use. LwWDG was designed to implement software watchdog functionality,
primarly used in the operating systems.

Each task in the system defines its very own Watchdog structure, and is responsible to periodically call reload function,
while one of the tasks, (it can be) called ``master`` task checks the processing function,
and reloads hardware watchdog, if everything is fine.

When one of the software watchdogs isn't reloaded within maximum timeout window, main task does not reload
hardware watchdog anymore, and therefore hardware will trigger the hardware reset.

Example
^^^^^^^

A simple example to illustrate functionality.

.. literalinclude:: ../../examples/example_win32.c
    :language: c
    :linenos:
    :caption: WIN32 example code

.. toctree::
    :maxdepth: 2

