package paquete_buffer is

   -- Definir e inicializar la constante Tamanio_Buffer de tipo entero
   tamanio_buffer:constant Integer:=10;

   -- Definir el tipo Index_t que sea un rango entre 0 a Tamanio_Buffer-1 (usar mod Tamanio_Buffer)
   type index_t is mod tamanio_buffer;

   -- Definir un subtipo Cuenta_t basado en el tipo Natural que vaya de 0 a Tamanio_Buffer
   subtype cuenta_t is Natural range 0..tamanio_buffer;

   -- Definir el tipo Buffer_t como un array de enteros en el rango Index_t
   type buffer_t is array (index_t) of Integer;

   -- Definir el objeto protegido Buffer_Acotado_t
   protected type buffer_acotado_t is

      -- Añadir la entrada Pon que reciva el dato a insertar
      entry pon(dato:in Integer);

      -- Añadir la entrada Quita que devuelva el dato leído
      entry quita(dato: out Integer);

   -- definir la zona privada del objeto
   private

      -- Definir e inicializar el atributo Primero de tipo Index_t (usar Index_t'First para la inicialización)
      primero:index_t:=index_t'First;

      -- Definir e inicializar el atributo Ultimo de tipo Index_t (usar Index_t'First para la inicialización)
      ultimo:index_t:=index_t'First;

      -- Definir e inicializar el atributo Cuenta de tipo Cuenta_t
      cuenta:cuenta_t:=0;

      -- Definir el atributo Buffer de tipo Buffer_t
      Buffer:buffer_t;

      --Final del objeto protegido Buffer_Acotado_t
   end;
end paquete_buffer;
