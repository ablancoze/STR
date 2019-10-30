with GNAT.IO;  use GNAT.IO;
with paquetebarrera;  use paquetebarrera;

procedure Main is

   -- Definir una constante NumTareas para indicar el n�mero de tareas que se bloquear�n en la barrera
   nTareas:Integer:=10;

   -- Definir el tipo PBarrera_t de tipo puntero a Barrera_t
   type pBarrera_t is access all barrera_t;

   -- Definir una variable B de tipo Barrera_t permitiendo que se acceda a su direcci�n de memoria (aliased). Usaremos NumTareas como par�metro constructor
   b:aliased barrera_t(nTareas);

   -- Dejinir el tipo tarea EntrandoEnBarrera con un par�metro B de tipo PBarrera_t
   task type entrandoEnBarrera(b:pBarrera_t);

   -- Implementar el cuerpo del tipo tarea
   task body entrandoEnBarrera
   is begin

      Put_Line("Entrando en la barrera");

      -- Invocar al procedimiento SincronizarEnBarrera pasando B.all como par�metro (B es un puntero a Barrera_t y el procedimiento recibe un Barrera_t)
      sincronizarEnBarrera(b.all);

      Put_Line("Saliendo de la barrera");

   end;

   -- Definir un array de tipo EntrandoEnBarrera con NumTareas elementos. Usar la direcci�n de B ('Access) como par�metro de EntrandoEnBarrera
   vector:array(1 .. nTareas) of entrandoEnBarrera(b'Access);
begin
   null;
end Main;
