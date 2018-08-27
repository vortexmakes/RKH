Overview
========

RKH is a generic, flexible, modular, highly portable, ANSI-C compliant, 
and open-source development tool for implementing hierarchical 
state machines based on modern state machine concepts. This modern 
techniques are used to give an abstract description of the dynamic 
behavior of a system in a substantial manner.

The main features of RKH
========================

- State machines representation is based on state tables.
- Representing a state machine with RKH is intuitive, and easy.
- Reflects the state diagram without obfuscation.
- The RKH application are highly maintainable.
- Provide the test harness to develop based on test.
- Easy to integrate with any event queuing and dispatching mechanism.
- Useful in embedded systems.
- The most of the RKH implementation is independent of any particular CPU, 
  operating system, or compiler.
- Flexible and user-configurable code generation.
- Very small footprint.
- Include a dispatching event mechanism based on active object's priority.
- Include a queue module
- Include a software timer module.
- Include a fixed-size memory block module.
- Include a native tracing tool.
- Support hierarchically nested states, and flat state machine.
- Support multiple state machines.
- Support final state.
- Support junction, branch and history (shallow and deep) pseudostates.
- Support compound transitions with guards.
- Support submachine state.
- Support local, internal and completion transitions.
- Support entry and exit actions.
- Support any kind of vertex as target of a default transition 
  in both composite state region or root region, according to UML 2.x.
- Implement the traditional transition sequence.
- Include mechanism for deferring events.
- Support event dispatching with parameters.
- Include dynamic events.
- Support a easy way to use events with arguments.
- Support systems-friendly assertion macros like assert, allege, error, 
require, and ensure.

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

RKH site: http://vortexmakes.com/que-es/

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
