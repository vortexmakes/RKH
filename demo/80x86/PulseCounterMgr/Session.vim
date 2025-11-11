let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/workspace
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +11 doc/examples/Blinky/Blinky-template-min.c
badd +19 doc/examples/Blinky/Blinky-template.c
badd +3 doc/examples/Blinky/Blinky-template-min.h
badd +5 doc/examples/Blinky/Blinky-template.h
badd +58 doc/examples/Blinky/Blinky.c
badd +1 doc/examples/Blinky/Blinky.h
badd +94 source/fwk/inc/rkh.h
badd +156 doc/examples/Monitor/Monitor.c
badd +29 doc/examples/Monitor/Monitor.h
badd +19 doc/examples/SignalMgr/SignalMgr.c
badd +27 doc/examples/SignalMgr/SignalMgr.h
badd +1 doc/examples/SignalMgr/SignalMgr_v4.c
badd +21 doc/examples/SignalMgr/SignalMgr_v2.c
badd +1 doc/examples/SignalMgr/SignalMgr_v3.c
badd +39 doc/examples/SignalMgr/events.h
badd +1352 source/sm/inc/rkhsm.h
badd +9 doc/examples/SignalMgr/CMakeLists.txt
badd +15 demo/80x86/blinky/CMakeLists.txt
badd +91 demo/80x86/blinky/README.md
badd +10 demo/80x86/SignalMgr/CMakeLists.txt
badd +21 demo/80x86/SignalMgr/src/CMakeLists.txt
badd +529 term://~/workspace//22457:fish
badd +33 demo/80x86/SignalMgr/src/main.c
badd +27 demo/80x86/SignalMgr/src/SignalMgr.h
badd +27 demo/80x86/SignalMgr/src/Actuator.c
badd +16 demo/80x86/SignalMgr/src/Sensor.c
badd +34 demo/80x86/SignalMgr/src/Sensor.h
badd +10 demo/80x86/SignalMgr/src/Actuator.h
badd +13 demo/80x86/blinky/src/bsp.h
badd +82 demo/80x86/SignalMgr/src/bsp.c
badd +18 demo/80x86/blinky/src/main.c
badd +56 demo/libbsp/platform/80x86/linux/bsp_blinky.c
badd +35 demo/cross/blinky/blinky.h
badd +18 demo/80x86/SignalMgr/src/SignalMgrV1/SignalMgr.c
badd +217 source/sma/inc/rkhsma.h
badd +218 source/sma/src/rkhsma.c
badd +502 demo/80x86/SignalMgr/rkhcfg.h
badd +164 demo/libbsp/platform/80x86/linux/hook.c
badd +90 source/tmr/inc/rkhtmr.h
badd +212 source/portable/80x86/linux_st/gnu/rkhport.c
badd +91 source/queue/src/rkhqueue.c
badd +44 demo/80x86/SignalMgr/src/events.h
badd +56 source/trc/inc/rkhtrc_filter.h
badd +842 source/trc/inc/rkhtrc_define.h
badd +718 source/sm/src/rkhsm.c
badd +2113 source/trc/inc/rkhtrc_record.h
badd +32 demo/80x86/SignalMgr/src/bsp.h
badd +217 source/trc/src/rkhtrc_record.c
badd +16 CMakeLists.txt
badd +1 demo/80x86/SignalMgr/src/SignalMgrV2/SignalMgr.c
badd +1 demo/80x86/SignalMgr/src/SignalMgrV3/SignalMgr.c
badd +2414 source/fwk/inc/rkhitl.h
badd +79 source/fwk/inc/rkhevt.h
badd +46 demo/80x86/SignalMgr/.vimspector.json
badd +0 term://~/workspace/demo/80x86/SignalMgr//91902:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//92269:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//92532:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//92682:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//92943:/bin/sh
badd +57 demo/80x86/SignalMgr/src/SignalMgrV4/SignalMgr.c
badd +0 term://~/workspace/demo/80x86/SignalMgr//97298:/bin/sh
badd +54 doc/examples/Monitor/events.h
badd +33 doc/examples/Monitor/priority.h
badd +47 demo/80x86/Monitor/src/Monitor.c
badd +38 demo/80x86/Monitor/src/Monitor.h
badd +26 demo/80x86/Monitor/src/priority.h
badd +8 demo/80x86/Monitor/src/signals.h
badd +6 demo/80x86/Monitor/src/CMakeLists.txt
badd +10 demo/80x86/Monitor/CMakeLists.txt
badd +33 demo/80x86/Monitor/src/main.c
badd +132 demo/80x86/Monitor/src/bsp.c
badd +8 demo/80x86/Monitor/.vimspector.json
badd +0 term://~/workspace/demo/80x86/Monitor//104671:/bin/sh
badd +0 term://~/workspace/demo/80x86/Monitor//105600:/bin/sh
badd +0 term://~/workspace/demo/80x86/Monitor//106277:/bin/sh
badd +41 demo/80x86/Monitor/src/events.h
badd +121 source/fwk/inc/rkhfwk_module.h
badd +0 term://~/workspace/demo/80x86/Monitor//111354:/bin/sh
badd +10 term://~/workspace/demo/80x86/Monitor//112027:/bin/sh
badd +17 term://~/workspace/demo/80x86/Monitor//112358:/bin/sh
badd +0 term://~/workspace/demo/80x86/Monitor//112984:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//114012:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//115533:/bin/sh
badd +20 term://~/workspace/demo/80x86/SignalMgr//115994:/bin/sh
badd +16 term://~/workspace/demo/80x86/SignalMgr//116700:/bin/sh
badd +0 term://~/workspace/demo/80x86/SignalMgr//117293:/bin/sh
badd +29 demo/80x86/Parameterized/src/priority.h
badd +2 demo/80x86/Parameterized/src/Parameterized.h
badd +21 demo/80x86/Parameterized/src/Parameterized.c
badd +2 demo/80x86/Parameterized/CMakeLists.txt
badd +8 demo/80x86/Parameterized/src/CMakeLists.txt
badd +1 demo/80x86/Parameterized/src/bsp.h
badd +146 demo/80x86/Parameterized/src/bsp.c
badd +28 doc/examples/PulseCounterMgr/PulseCounterMgr.h
badd +39 demo/80x86/PulseCounterMgr/src/PulseCounterMgr.h
badd +19 doc/examples/PulseCounterMgr/PulseCounterMgr.c
badd +268 demo/80x86/PulseCounterMgr/src/PulseCounterMgr.c
badd +38 doc/examples/PulseCounterMgr/events.h
badd +29 demo/80x86/PulseCounterMgr/src/events.h
badd +19 demo/80x86/PulseCounterMgr/src/signals.h
badd +7 demo/80x86/PulseCounterMgr/src/CMakeLists.txt
badd +29 demo/80x86/PulseCounterMgr/src/priority.h
badd +56 demo/80x86/PulseCounterMgr/src/bsp.c
badd +206 source/fwk/inc/rkhfwk_dynevt.h
badd +18 demo/80x86/PulseCounterMgr/src/main.c
badd +19 term://~/workspace/demo/80x86/PulseCounterMgr//140567:/bin/sh
badd +0 term://~/workspace/demo/80x86/PulseCounterMgr//141030:/bin/sh
badd +15 demo/80x86/PulseCounterMgr/.vimspector.json
badd +10 demo/80x86/PulseCounterMgr/CMakeLists.txt
badd +61 demo/80x86/PulseCounterMgr/Session.vim
argglobal
%argdel
edit demo/80x86/Parameterized/src/Parameterized.c
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt doc/examples/SignalMgr/CMakeLists.txt
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 21 - ((11 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 21
normal! 05|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
