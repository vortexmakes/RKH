[![Build Status](https://travis-ci.com/vortexmakes/RKH.svg?branch=pubsub)](https://travis-ci.com/vortexmakes/RKH) [![codecov](https://codecov.io/gh/vortexmakes/RKH/branch/pubsub/graph/badge.svg)](https://codecov.io/gh/vortexmakes/RKH)

Overview
========

RKH is a generic, flexible, modular, highly portable, ANSI-C compliant, 
and open-source development tool for implementing hierarchical 
state machines based on modern state machine concepts. This modern 
techniques are used to give an abstract description of the dynamic 
behavior of a system in a substantial manner.

[![RKH architecture](doc/images/rkh_arch_small.png)](https://vortexmakes.com/rkh/)

The main features of RKH
========================

- State machines representation is based on state tables.
- Representing a state machine with RKH is intuitive, and easy.
- Reflects the state diagram without obfuscation.
- RKH applications are highly maintainable.
- Provides the test harness to develop based on TDD.
- Easy to integrate with any event queuing and dispatching mechanism.
- Useful in embedded systems.
- The most of the RKH implementation is independent of any particular CPU, 
  operating system, or compiler.
- Flexible and user-configurable code generation.
- Very small footprint.
- Includes a dispatching event mechanism based on active object's priority.
- Includes a queue module
- Includes a software timer module.
- Includes a fixed-size memory block module.
- Includes a native tracing tool.
- Supports hierarchically nested states, and flat state machine.
- Supports multiple state machines.
- Supports final state.
- Supports junction, branch and history (shallow and deep) pseudostates.
- Supports compound transitions with guards.
- Supports submachine state.
- Supports local, internal and completion transitions.
- Supports entry and exit actions.
- Supports any kind of vertex as target of a default transition 
  in both composite state region or root region, according to UML 2.x.
- Implements the traditional transition sequence.
- Includes mechanism for deferring events.
- Supports event dispatching with parameters.
- Includes dynamic events.
- Supports a easy way to use events with arguments.
- Supports systems-friendly assertion macros like assert, allege, error, 
require, and ensure.

Examples
========

Repo [rkh-examples](https://github.com/vortexmakes/rkh-examples) contains a 
collection of open source examples based on RKH framework to develop embedded 
software for several platforms. In this context, it refers to combination of 
CPU architecture, compiler or IDE, and operating system. Also, rkh-examples 
includes some demostrative and cross-platform applications running under 
Windows and Linux to improve and fast development cycle.

# Other embedded applications based on RKH framework
- [DIMBA](https://github.com/vortexmakes/dimba): IoT application, using MQTT protocol over GSM network.

Documentation
=============

Documentation and license info exists in the [reference manual](https://vortexmakes.com/rkh/).

Purpose and inspiration
=======================

For many years, I had been used the traditional state-machine concepts 
based on state-table strategy for modeling the dynamic behavior of several 
reactive-systems, in many industries. Over the years, this implementation 
was expanding its abilities to support system requirements increasingly 
complex, achieving hierarchically nested states, pseudostates, compound 
transitions, and more, proposed by Harel Statecharts.

The RKH not implements neither entire UML specs. nor entire Statechart 
specs. Instead, the RKH intention is to support just enough basic concepts 
of that powerful tools to facilitate the reactive-system modeling holding 
a solid, and efficient implementation. Broadly speaking, the RKH 
implementation has been designed from the ground up to be used in 8-bits 
platforms but can be easily adapted to 16 or 32-bits platforms.

Other implementations
=====================

Open-source frameworks that support Statecharts.

Quantum Leap - [http://www.state-machine.com/](http://www.state-machine.com/)

Licensing
=========

Copyright (C) 2010 Leandro Francucci. All rights reserved.

RKH is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software 
Foundation, either version 3 of the License, or (at your option) any later 
version.

RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with 
RKH package. If not, see <http://www.gnu.org/licenses/>.

(*)  Observe that, the GPLv3 can be used for research & development and 
     educational purposes (academic purposes).

(**) When the source code of your application should not be published under 
     the GNU GPLv3 license (closed source code), please, contact contact me. 
     See Contact information section.

Contact information
===================

Official site: http://vortexmakes.com/que-es/
RKH GitHub: https://github.com/vortexmakes/RKH
RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
e-mail: lf@vortexmakes.com

RKH Release notes
=================

Changes between V3.0.0 and V3.1.0 released 03/05/2018

- Added support for using any kind of vertex as target of a default transition 
  in both composite state region or root region, according to UML 2.x.
- The RKH_TE_SM_NTRNACT trace record is now deprecated and not recommended 
  for new designs. It remains supported for backwards compatibility.
