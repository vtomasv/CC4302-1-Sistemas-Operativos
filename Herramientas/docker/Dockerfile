#===============================================================================
#|        _____           _
#|       / ____|         | |
#|  _ __ | (___  _   _ ___| |_ ___ _ __ ___
#|  | '_ \ \___ \| | | / __| __/ _ \ '_ ` _ \
#|  | | | |____) | |_| \__ \ ||  __/ | | | | |
#|  |_| |_|_____/ \__, |___/\__\___|_| |_| |_|
#|               __/ |        Prof. Luis Mateu
#|              |___/
#| - CC41B Sistemas Operativos | DCC | Universidad de Chile
#===============================================================================


# ==============================================================================
# |        Documentacion de Controles de cambio                    |
# ==============================================================================
# @author Tomas Vera <tvera@kvz.cl>
# @doc
# @copyleft 2017
# @title Receta Docker para nSystem
# ==============================================================================
# | Historial de cambios
# ==============================================================================
# | {Cambio, ID-REQ, Fecha, Responsable}
# ==============================================================================

# ==============================================================================
# Definicion de la imagen
# ==============================================================================

FROM  alpine:3.5
MAINTAINER vtomasv - Tomas Vera - tvera@dcc.uchile.cl

# Se configura la variable de ambiente para nSystem
ENV NSYSTEM /usr/src/nsystem64-beta2

# Se instalan todas las herramientas de desarrollo que se puedan necesitar
RUN apk add --no-cache  gcc musl-dev build-base  abuild binutils binutils-doc gcc-doc cmake cmake-doc tar gzip

# Se crea el directorio de trabajo
RUN mkdir -p /usr/src
COPY nsystem64-beta2.tgz /usr/src
WORKDIR /usr/src
RUN gunzip -c nsystem64-beta2.tgz | tar xvf -
RUN mkdir /usr/src/nsystem64-beta2/tareas

VOLUME /usr/src/nsystem64-beta2/tareas

WORKDIR /usr/src/nsystem64-beta2/tareas
