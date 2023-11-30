# operating_systems

Configuracion del entorno. 

1. Confiurar wsl en Windows
	
	1.1 Abre PowerShell como administrador

	1.2 Ejecuta el siguiente comando para habilitar WSL: 
		
		dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
	
	1.3 Habilita la característica Hyper-V (si es necesario):

		dism.exe /online /enable-feature /featurename:Microsoft-Hyper-V-All /all /norestart

	1.4 Reinicia tu equipo 

2. Instalación de una distribución de Linux

	2.1 Abre la Microsoft Store:
		
		Busca "Linux" en la Microsoft Store y elige una distribución de tu preferencia, como Ubuntu, Debian o Fedora.

	2.2 Configura tu nueva distribución de Linux:

		Después de instalarla, se te pedirá que establezcas un nombre de usuario y una contraseña para la cuenta de administrador.

	2.3 Espera a que se complete la instalación.


3. Configurar Docker en Windows

	Descarga e instala Docker Desktop para Windows desde el sitio oficial de Docker (https://www.docker.com/products/docker-desktop).

	
	Apartir de la seccion 3.4 la configuracion cambia segun la arquitectura, te invito a revisar que arquitectura deseas implementar ( se encuentran en la partre inferior del readme )
	
	
	3.1 Si la configuracion no esta habilitada sigue estos pasos: 
	
		I. Abre Docker Desktop:	Asegúrate de que Docker Desktop esté instalado y en ejecución en tu sistema Windows.
		
		II. Accede a Configuración:

			- Haz clic en el ícono de Docker Desktop en la bandeja del sistema.
			- Selecciona "Settings" (Configuración).

		III. Configura WSL:

			- En la sección izquierda, selecciona "General".
			- Habilita la opción "Use the WSL 2 based engine" (Usar el motor basado en WSL 2).
			- Asegúrate de que la distribución de WSL que estás utilizando esté seleccionada en la sección "WSL Integration".
		
		IV. Aplica los Cambios:	Haz clic en "Apply & Restart" (Aplicar y reiniciar) para aplicar los cambios.

		V. Verifica la Integración: Abre una terminal de WSL y ejecuta "docker ps" para verificar que ahora se puede acceder al comando 'docker' desde WSL.

	3.2 Verifica las Credenciales: 
	
		- Asegúrate de que estás utilizando el nombre de usuario y la contraseña correctos al iniciar sesión. 
		- Puedes verificar tus credenciales en la página web de Docker Hub.
		- Si no tienes un usuario crea uno para poder descargar las imagenes. 
 
	3.3 Crea un nuevo directorio para tu proyecto y colócate en él desde la terminal con los siguientes comandos: 

		- mkdir mi_proyecto
		- cd mi_proyecto

	3.4 Crea un Archivo Dockerfile ().

	3.5 Copia el archivo a ejecutar en el directorio creado. 

	3.6 Construir la Imagen.

	3.7. Ejecutar el Contenedor. 




# Configuracion para la arquitectura ARM

1. Copiamos el archivo dijkstra.c en la ruta donde vamos a generar nuestro docker. 

2. Abrimos una terminal wsl como administrador y nos ubicamos en la ruta deseada con el siguiente comando ( recuerda que la direccion es difrente para tu equipo ajustala como sea necesario ): 

		cd /mnt/c/Users/sp_ca/OneDrive/Escritorio/Sistemasoperativos/ARM

3. Creamos el arcivo docker file con el siguiente comando:

		nano Dockerfile 

4. En la terminal copiamos el archivo con la siguiente estructura para la arquitectura ARM:

		#Dockerfile para una imagen ARM
		FROM arm32v7/gcc:latest

		#Instala qemu-user-static para habilitar la emulación de arquitectura
		RUN apt-get update && apt-get install -y qemu-user-static

		#WORKDIR /app
		COPY dijkstra.c .

        	#Compila el código fuente
		RUN gcc -o dijkstra dijkstra.c

		#Comando por defecto al ejecutar el contenedor
		CMD ["./dijkstra"]


5. Contruimos la imagen con el siguiente comando: 

		docker build -t dijkstra-arm -f Dockerfile --platform linux/arm/v7 .

6. Corremos la imagen con el siguiente comando: 

		docker run --platform linux/arm/v7 dijkstra-arm

7. Verificamos la arquitectura del contenedor con el siguiente comando: 

		docker inspect --format='{{.Architecture}}' dijkstra-arm

8. Ejecutamos y medimos el tiempo de ejecucion del algoritmo con el siguiente comando: 

		time docker run --platform linux/arm/v7 dijkstra-arm


# Configuracion para la arquitectura X86


1. Copiamos el archivo dijkstra.c en la ruta donde vamos a generar nuestro docker. 

2. Abrimos una terminal wsl como administrador y nos ubicamos en la ruta deseada con el siguiente comando ( recuerda que la direccion es difrente para tu equipo ajustala como sea necesario ):  

		cd /mnt/c/Users/sp_ca/OneDrive/Escritorio/Sistemasoperativos/X86

3. Creamos el arcivo docker file con el siguiente comando:

		nano Dockerfile 

4. En la terminal copiamos el archivo con la siguiente estructura para la arquitectura x86:

        	#Dockerfile para una imagen x86
		FROM gcc:latest

		#Establece el directorio de trabajo dentro del contenedor
		WORKDIR /app

   		#Copia el código fuente al directorio de trabajo del contenedor
		COPY dijkstra.c .

   		#Compila el programa
		RUN gcc -o dijkstra dijkstra.c

   		#Comando por defecto al ejecutar el contenedor
		CMD ["./dijkstra"]

5. Contruimos la imagen con el siguiente comando: 

		docker build -t dijkstra-x86 .

6. Corremos la imagen con el siguiente comando: 

		docker run dijkstra-x86

7. Verificamos la arquitectura del contenedor con el siguiente comando: 

		docker inspect --format='{{.Architecture}}' dijkstra-x86

8. Ejecutamos y medimos el tiempo de ejecucion del algoritmo con el siguiente comando: 

		time docker run dijkstra-x86
