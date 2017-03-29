#!/usr/bin/env bash
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
# @title Start de maquina Docker para nSystem
# ==============================================================================
# | Historial de cambios
# ==============================================================================
# | {Cambio, ID-REQ, Fecha, Responsable}
# ==============================================================================

# ==============================================================================
# Definicion de la imagen
# ==============================================================================

docker run -v /Users/vtomasv/Documents/workspace/so/tareas:/usr/src/nsystem64-beta2/tareas -dti vtomasv/nsystem /bin/sh
