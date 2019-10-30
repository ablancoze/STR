package paquetebarrera is

   -- Definir el tipo Barrera_t privado y limitado para poder usarlo fuera del paquete
   type barrera_t(numTareas:Integer:=10)is limited private;

   -- Definir el procedimiento SincronizarEnBarrera con un par�metro de entrada salida de tipo Barrera_t
   procedure sincronizarEnBarrera(barrera: in out barrera_t);

   -- Definir el procedimiento ResetearBarrera con un par�metro de entrada salida de tipo Barrera_t
   procedure resetBarrera(barrera: in out barrera_t);

private

   -- Definir el objeto protegido Barrera_t. Recibir� un par�metro con el n�mero de tareas que bloquear� (10 por defecto)
   protected type barrera_t(numTareas:Integer:=10) is

      -- Definir el procedimiento Entrando
      procedure entri;

      -- Definir la entrada Wait
      entry wait;

      -- Definir el procedimiento Resetear
      procedure reset;

   -- Definir la regi�n privada del objeto protegido
   private

      -- Definir la variable Cont e inicializarla a 0
      cont:Integer:=0;

      -- Definir la variable NumTareas e inicializarla a Tareas (par�metro de creaci�n del objeto protegido)
      nTareas:Integer:=numTareas;

   -- Fin del objeto protegido
   end;
end paquetebarrera;
