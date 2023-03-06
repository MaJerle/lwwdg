.. _um:

User manual
===========

LwWDG library is very simple and easy to use. LwWDG was designed to implement software watchdog functionality,
primarily used in the operating systems.

Each task in the system defines its very own Watchdog structure, and is responsible to periodically call reload function,
while one of the tasks, (it can be) called ``master`` task checks the processing function,
and reloads hardware watchdog, if everything is fine.

When one of the software watchdogs isn't reloaded within maximum timeout window, main task is not supposed to reload hardware timer anymore.
As a consequence, hardware watchdog will reset the system.

.. note::
    This library is designed for operating system, where operations are splitted in the tasks.
    To ensure stable operation, each task should have a monitoring system.

    Since microcontrollers typical utilize single independent watchdog, such solution must be implemented
    as a combination of hardware and software components.

Platform migration
^^^^^^^^^^^^^^^^^^

Library requires atomicity in the processing function, and a milliseconds time source.
These should be implemented as macros in the configuration file. Checkout the configuration window or follow to example mentioned below.

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

