cliente ftp

comandos

	SI	NO SE	NO	COMENTARIO
acceso
	user	smnt
    	pass	acct
    	cwd
	cdup
    	rein			falta flush
    	quit
transfer
	port			anda,falta lo del ip local
	pasv
			type    toma 2 argumentos,falta implementacion para cada tipo
	stru			falta implementacion para cada estructura
	mode			falta implementacion para cada modo
servicios
	retr			nombre del archivo mal
			stor    no implementado
			stou	no implementado
			appe	no implementado
		allo
		rnfr
		rnto
	abor			anda,que hace?
		dele	
		rmd
		mkd
	pwd
	list			despues de pasv
			nlst	leer desde datos
	site
	syst
		help
	noop

NO ESPERAR QUE FUNCIONE CORRECTAMENTE