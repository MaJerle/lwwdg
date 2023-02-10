.. _um:

User manual
===========

LwWDG library is very simple and easy to use. LwWDG was designed to implement software watchdog functionality,
primarily used in the operating systems.

Each task in the system defines its very own Watchdog structure, and is responsible to periodically call reload function,
while one of the tasks, (it can be) called ``master`` task checks the processing function,
and reloads hardware watchdog, if everything is fine.

When one of the software watchdogs isn't reloaded within maximum timeout window, main task does not reload
hardware watchdog anymore, and therefore hardware will trigger the hardware reset.

Platform migration
^^^^^^^^^^^^^^^^^^

Library requires atomicity in the processing function, and a milliseconds time.
These should be implemented as macro. Checkout the configuration window.

Example
^^^^^^^

A simple example to illustrate functionality.

.. literalinclude:: ../../examples/example_win32.c
    :language: c
    :linenos:
    :caption: WIN32 example code

A corresponding options file, that must be updated for Win32 port.

.. literalinclude:: ../../dev/lwwdg_opts.h
    :language: c
    :linenos:
    :caption: WIN32 LwWDG options file

.. toctree::
    :maxdepth: 2

