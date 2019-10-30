with GNAT.IO; use GNAT.IO;

package body paquete_buffer is
   
   -- Definir el cuerpo del objeto protegido Buffer_Acotado_t
   protected body buffer_acotado_t is
   
     -- A�adir la la entrada Pon (misma cabecera que en el fichero .ads)
     entry pon(dato: in Integer)
   
       -- A�adir la condici�n de acceso a la entrada (buffer no lleno)
       when cuenta < tamanio_buffer
   
     -- Comienzo del c�digo de la entrada Pon
     is begin
       -- A�adir Item a la posici�n Ultimo de Buffer
       buffer(ultimo):= Dato;
      
       -- Mostrar un mensaje indicando que se ha a�adido el dato almacenado en la posici�n Ultimo de Buffer
       put_line("Insertado el dato " & integer'Image(buffer(ultimo)));
		 
       -- Actualizar Ultimo
       ultimo:=ultimo+1;

       -- Actualizar Cuenta
       cuenta:=cuenta+1;

     --Fin del c�digo de la entrada Pon
     end;

     -- A�adir la la entrada Quita (misma cabecera que en el fichero .ads)
     entry quita(dato: out Integer)

       -- A�adir la condici�n de acceso a la entrada (buffer no vac�o)
       when cuenta > 0

     -- Comienzo del c�digo de la entrada Quita
     is begin
       -- Almacenar en Item el contenido de la posici�n Primero de Buffer
       dato:=buffer(primero);
		 
       -- Actualizar Primero
       primero:=primero+1;
        
       -- Actualizar Cuenta
       cuenta:=cuenta-1;

       -- Mostrar un mensaje indicando que se ha leido el dato Item
       put_line("Sacando el dato " & integer'Image(dato));

     --Fin del c�digo de la entrada Quita
     end;
	  
   -- Fin del cuerpo del del objeto protegido Buffer_Acotado_t
   end;
end paquete_buffer;
