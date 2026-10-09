:userdoc.
:title.Ayuda de STris
:docprof toc=12.
:h1 res=1000.General
:p.STris es un clon de Tetris para OS/2 Presentation Manager, escrito originalmente por Rene Straub (1995-1996).
:p.Piezas de cuatro bloques caen en el campo de juego. Mu&ea.velas y gr&ia.ralas para llenar l&ia.neas horizontales completas. Una l&ia.nea completa desaparece y da puntos. El juego termina cuando no queda sitio para una pieza nueva.
:p.Use el men&ua. Ayuda para los temas C&oa.mo jugar, Teclas y Opciones, o pulse F1 en cualquier di&aa.logo.
:p.:link reftype=hd res=4000.C&oa.mo jugar:elink.
:p.:link reftype=hd res=4100.Las teclas:elink.
:p.:link reftype=hd res=11000.Opciones:elink.
:p.:link reftype=hd res=2200.Acerca de STris:elink.
:h1 res=4000.C&oa.mo jugar
:p.Dirija las piezas que caen para llenar l&ia.neas horizontales. Eliminar varias l&ia.neas a la vez da m&aa.s puntos. Empezar en un nivel m&aa.s alto o con m&aa.s velocidad tambi&ea.n da m&aa.s puntos.
:p.La pieza se controla con las teclas indicadas en Teclas. Con el avance del juego las piezas caen m&aa.s r&aa.pido.
:p.Elija Iniciar juego (Ctrl+N) para empezar. Pausa (Ctrl+P) detiene el juego, Terminar juego (Ctrl+Q) finaliza la partida actual y Salir (Ctrl+X) cierra el programa.
:h1 res=4100.Las teclas
:p.Estas son las teclas predeterminadas. Pueden cambiarse en el di&aa.logo Definir teclas (men&ua. Opciones).
:table cols='26 22 10' rules=both frame=box.
:row.:c.:hp2.Funci&oa.n:ehp2.:c.:hp2.Tecla:ehp2.:c.:hp2.Bloq Num:ehp2.
:row.:c.Mover a la izquierda:c.Cursor izquierda:c.4
:row.:c.Mover a la derecha:c.Cursor derecha:c.6
:row.:c.Girar:c.Cursor arriba:c.8
:row.:c.Bajar m&aa.s r&aa.pido:c.Cursor abajo:c.2
:row.:c.Pausa:c.Pausa o Ctrl+P:c. 
:etable.
:p.Para usar el teclado num&ea.rico debe estar activado Bloq Num. El giro en el otro sentido no tiene tecla por defecto; as&ia.gnele una en Definir teclas.
:p.:hp2.Atajos:ehp2.
:table cols='12 50' rules=both frame=box.
:row.:c.Ctrl+N:c.Nueva partida (se ignora si hay una partida en curso)
:row.:c.Ctrl+P:c.Pausa / continuar
:row.:c.Ctrl+Q:c.Terminar la partida actual (se ignora si no hay partida)
:row.:c.Ctrl+X:c.Salir del programa
:row.:c.Ctrl+B:c.Ejecuci&oa.n en segundo plano s&ia./no
:row.:c.Ctrl+F:c.Controles del marco s&ia./no
:etable.
:h1 res=11000.Opciones
:p.El di&aa.logo de configuraci&oa.n y el men&ua. Opciones cambian el juego. Todo se guarda al salir si Guardar configuraci&oa.n al salir est&aa. marcado.
:parml tsize=22 break=none.
:pt.Velocidad
:pd.Velocidad inicial de ca&ia.da de las piezas.
:pt.Nivel inicial
:pd.Cada nivel empieza con una l&ia.nea m&aa.s llena al azar.
:pt.Sonido
:pd.Efectos de sonido s&ia./no. Desactivado si no hay sonido disponible.
:pt.Rejilla
:pd.Rejilla en el campo de juego, &ua.til al soltar piezas.
:pt.Pr&oa.xima pieza
:pd.Muestra la siguiente pieza.
:pt.Permanecer en pausa
:pd.Mantiene la pausa cuando la ventana recupera el foco.
:pt.Paleta
:pd.Selecciona un mapa de colores.
:pt.Color s&oa.lido
:pd.Usa solo colores s&oa.lidos (pantallas de 16 colores).
:pt.Empezar con casillas extra
:pd.Llena al azar filas abajo&colon. tantas como indique el nivel inicial, o 4 si es 0. Desactivado = campo vac&ia.o.
:pt.Detalle
:pd.Detalle de dibujo alto, medio o bajo.
:pt.Idioma
:pd.Idioma de la interfaz y de la ayuda (ingl&ea.s, espa&nt.ol, neerland&ea.s, alem&aa.n, franc&ea.s, italiano).
:pt.Ejecutar en segundo plano
:pd.Si est&aa. marcado, el juego sigue cuando STris no es la ventana activa. Si no, se pone en pausa solo.
:pt.Controles del marco
:pd.Muestra u oculta la barra de t&ia.tulo y el men&ua. (juego sin bordes). La ventana cambia de tama&nt.o sola.
:pt.Guardar configuraci&oa.n al salir
:pd.Guarda la configuraci&oa.n en STris.cfg al salir. Activado por defecto.
:eparml.
:h1 res=12000 hide.Mejores puntuaciones
:p.El sal&oa.n de la fama de los mejores jugadores.
:h1 res=13000 hide.Introducir nombre
:p.Ha logrado una puntuaci&oa.n para el sal&oa.n de la fama. Escriba su nombre en el campo.
:h1 res=14000 hide.Definir teclas
:p.Seleccione la funci&oa.n cuya tecla quiere cambiar pulsando su bot&oa.n y pulse la nueva tecla. Esc cancela. Algunas teclas no se pueden usar; un mensaje se lo indica.
:p.El bot&oa.n Predeterminadas restaura las teclas est&aa.ndar.
:h1 res=2200.Acerca de STris
:p.STris 1.50 para OS/2, ArcaOS y eComStation.
:p.Autor original&colon. Rene Straub (1995-1996).
:p.Port a Open Watcom 2.0&colon. comunidad OS2World (2026).
:p.Licencia&colon. GNU General Public License v3. Vea LICENSE.txt.
:p.:link reftype=hd res=6000.Cambios en 1.50:elink.
:h1 res=6000.Cambios en 1.50
:ul compact.
:li.Portado a Open Watcom 2.0.
:li.Men&ua.s&colon. Juego, Opciones (con Idioma), Ayuda; atajos est&aa.ndar.
:li.Seis idiomas para la interfaz y la ayuda.
:li.Ejecuci&oa.n en segundo plano, Controles del marco, Guardar configuraci&oa.n al salir.
:li.La pausa se desactiva al terminar una partida.
:eul.
:euserdoc.
