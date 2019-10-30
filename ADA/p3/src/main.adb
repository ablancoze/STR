with GNAT.IO; use GNAT.IO;
-- Incluir el paquete paquete_buffer (con with y use)
with paquete_buffer; use paquete_buffer;

procedure Main is
   
   -- Definir una variable de tipo buffer_acotado_t permitiendo el acceso a su dirección de memoria (usar la palabra reservada aliased delante del tipo)
   Buffer : aliased buffer_acotado_t;
  
   -- Definir un tipo PBuffer_Acotado_t de tipo puntero a Buffer_Acotado_t de la forma type TipoPuntero is access all TipoNoPuntero;
   type PBuffer_Acotado_t is access all buffer_acotado_t;
   
   -- Definir un tipo tarea TProductor con un parámetro B de tipo PBuffer_Acotado_t
   task type TProductor(b:PBuffer_Acotado_t);
   
   -- Implementar el cuerpo del tipo tarea TProductor
   task body TProductor
   
   --Comienzo del código de la tarea TProductor
   is begin

      -- Desde i igual 1 hasta 50
      for i in 1..50 loop
         
         -- Llamar al método Pon del objeto B con el parámetro i
         b.pon(i);
      
      -- Fin para
      end loop;
   
   -- Fin cuerpo de Tproductor
   end TProductor;

   
   
   -- Definir un tipo tarea Tconsumidorl con un parámetro B de tipo PBuffer_Acotado_t
   task type TConsumidor(b : PBuffer_Acotado_t);
   
   -- Implementar el cuerpo del tipo tarea Tproductor
   task body TConsumidor
   is 
   -- Definir una variable entera para almacenar el dato leído
   dato : Integer;
   
   -- Comienzo del código de la tarea Tconsumidorl
   begin
   
      -- Desde i igual 1 hasta 50
      for i in 1..50 loop
      
         -- Llamar al método Quita del objeto B con el parámetro d
         b.quita(dato);
     
      -- Fin para
      end loop;
   
      -- Fin cuerpo de Tconsumidor
   end TConsumidor;
   
   
   
   -- Definir una variable P de tipo array de 1 hasta 5 de tipo TProductor. Usar la dirección de Buffer como parámetro de entrada (atributo Access de Buffer)
   P:array(1..5)of TProductor(buffer'Access);
   
   -- Definir una variable C de tipo array de 1 hasta 5 de tipo TConsumidor. Usar la dirección de Buffer como parámetro de entrada (atributo Access de Buffer)
   C:array(1..5)of TConsumidor(buffer'Access);


begin
   null;
end Main;
