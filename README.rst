biztonsag
=========
|codacy|

A library that attempts to provide compile-time safety around ubiquitous types.


Motivation
----------
Many years ago, there was a post from `Joel On Software`_ that convinced me
Hungarian notation is good, provided that it's used correctly.  Since C++
provides strong types though, I've always toyed with the idea of writing code
to promote those code smells (the way Joel describes) to compilation errors.

This library is mostly for experimentation, although I expect it's suitable
for production use.


Building
--------
biztonsag is a header-only library.  It's designed to be installed via CMake_.

.. code:: bash

    $ cd /path/to/biztonsag
    $ mkdir build
    $ cd build
    $ cmake ..
    $ cmake --build .
    $ cmake --build . --target install

Unit tests are avialable (requires GTest_).

.. code:: bash

    $ cmake --build . --target test

Name Origin
-----------
Because biztonsag is an attempt to get the type-safety benefits of Hungarian
notation at compile-time, I enlisted `Google Translate`_.  While "típusú
biztonság" is a bit much, the second word fits my goals:

biztonság
  security, safety, behavior, behaviour


.. |codacy| image::
    https://api.codacy.com/project/badge/Grade/7a95931c6be34203be54a921983b5dc2
    :target: https://www.codacy.com/manual/snewell/biztonsag?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=snewell/biztonsag&amp;utm_campaign=Badge_Grade
.. _CMake: https://cmake.org
.. _Google Translate: https://translate.google.com/#view=home&op=translate&sl=auto&tl=hu&text=type%20safety
.. _GTest: https://github.com/google/googletest/
.. _Joel On Software: https://www.joelonsoftware.com/2005/05/11/making-wrong-code-look-wrong/
