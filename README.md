cliente ftp

comandos

	SI	NO SE	NO	COMENTARIO
acceso
	user
		smnt
    	pass
		acct
    	cwd
	cdup
    	rein			falta flush
    	quit
transfer
	port			anda,falta lo del ip local
	pasv
			type    toma 2 argumentos,ascii(a) ya esta.faltan image(i),ebcdict(e)
	stru			falta implementacion,file(f) ya esta.faltan record(r) y page(p)
	mode			falta implementacion,stream(s) ya esta.block(b) algo.falta compressed(c)
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