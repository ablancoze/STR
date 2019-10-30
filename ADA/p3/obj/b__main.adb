pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__main.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__main.adb");
pragma Suppress (Overflow_Check);

with System.Restrictions;
with Ada.Exceptions;

package body ada_main is
   pragma Warnings (Off);

   E011 : Short_Integer; pragma Import (Ada, E011, "system__soft_links_E");
   E021 : Short_Integer; pragma Import (Ada, E021, "system__exception_table_E");
   E123 : Short_Integer; pragma Import (Ada, E123, "ada__io_exceptions_E");
   E087 : Short_Integer; pragma Import (Ada, E087, "ada__tags_E");
   E122 : Short_Integer; pragma Import (Ada, E122, "ada__streams_E");
   E052 : Short_Integer; pragma Import (Ada, E052, "interfaces__c_E");
   E023 : Short_Integer; pragma Import (Ada, E023, "system__exceptions_E");
   E125 : Short_Integer; pragma Import (Ada, E125, "system__finalization_root_E");
   E120 : Short_Integer; pragma Import (Ada, E120, "ada__finalization_E");
   E145 : Short_Integer; pragma Import (Ada, E145, "system__storage_pools_E");
   E139 : Short_Integer; pragma Import (Ada, E139, "system__finalization_masters_E");
   E071 : Short_Integer; pragma Import (Ada, E071, "system__task_info_E");
   E147 : Short_Integer; pragma Import (Ada, E147, "system__pool_global_E");
   E015 : Short_Integer; pragma Import (Ada, E015, "system__secondary_stack_E");
   E116 : Short_Integer; pragma Import (Ada, E116, "system__tasking__initialization_E");
   E043 : Short_Integer; pragma Import (Ada, E043, "ada__real_time_E");
   E104 : Short_Integer; pragma Import (Ada, E104, "system__tasking__protected_objects_E");
   E112 : Short_Integer; pragma Import (Ada, E112, "system__tasking__protected_objects__entries_E");
   E131 : Short_Integer; pragma Import (Ada, E131, "system__tasking__queuing_E");
   E151 : Short_Integer; pragma Import (Ada, E151, "system__tasking__stages_E");
   E102 : Short_Integer; pragma Import (Ada, E102, "paquete_buffer_E");

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   Is_Elaborated : Boolean := False;

   procedure finalize_library is
   begin
      E112 := E112 - 1;
      declare
         procedure F1;
         pragma Import (Ada, F1, "system__tasking__protected_objects__entries__finalize_spec");
      begin
         F1;
      end;
      E139 := E139 - 1;
      E147 := E147 - 1;
      declare
         procedure F2;
         pragma Import (Ada, F2, "system__pool_global__finalize_spec");
      begin
         F2;
      end;
      declare
         procedure F3;
         pragma Import (Ada, F3, "system__finalization_masters__finalize_spec");
      begin
         F3;
      end;
      declare
         procedure Reraise_Library_Exception_If_Any;
            pragma Import (Ada, Reraise_Library_Exception_If_Any, "__gnat_reraise_library_exception_if_any");
      begin
         Reraise_Library_Exception_If_Any;
      end;
   end finalize_library;

   procedure adafinal is
      procedure s_stalib_adafinal;
      pragma Import (C, s_stalib_adafinal, "system__standard_library__adafinal");

      procedure Runtime_Finalize;
      pragma Import (C, Runtime_Finalize, "__gnat_runtime_finalize");

   begin
      if not Is_Elaborated then
         return;
      end if;
      Is_Elaborated := False;
      Runtime_Finalize;
      s_stalib_adafinal;
   end adafinal;

   type No_Param_Proc is access procedure;

   procedure adainit is
      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Main_CPU : Integer;
      pragma Import (C, Main_CPU, "__gl_main_cpu");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Leap_Seconds_Support : Integer;
      pragma Import (C, Leap_Seconds_Support, "__gl_leap_seconds_support");

      procedure Runtime_Initialize (Install_Handler : Integer);
      pragma Import (C, Runtime_Initialize, "__gnat_runtime_initialize");

      Finalize_Library_Objects : No_Param_Proc;
      pragma Import (C, Finalize_Library_Objects, "__gnat_finalize_library_objects");
   begin
      if Is_Elaborated then
         return;
      end if;
      Is_Elaborated := True;
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      System.Restrictions.Run_Time_Restrictions :=
        (Set =>
          (False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           True, False, False, False, False, False, False, False, 
           False, False, False, False, False, False),
         Value => (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
         Violated =>
          (True, False, False, True, True, False, False, False, 
           False, False, False, True, True, True, False, False, 
           True, False, False, True, True, False, True, True, 
           False, True, True, False, True, False, False, True, 
           False, True, False, True, True, False, True, False, 
           True, True, False, False, False, True, False, False, 
           False, True, False, False, False, False, True, False, 
           True, False, True, True, True, False, False, True, 
           False, False, True, False, True, True, False, True, 
           True, True, False, True, False, False, False, True, 
           False, False, True, False, True, False),
         Count => (0, 0, 0, 2, 0, 0, 1, 0, 1, 0),
         Unknown => (False, False, False, False, False, False, True, False, True, False));
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Main_CPU := -1;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;
      Leap_Seconds_Support := 0;

      Runtime_Initialize (1);

      Finalize_Library_Objects := finalize_library'access;

      System.Soft_Links'Elab_Spec;
      System.Exception_Table'Elab_Body;
      E021 := E021 + 1;
      Ada.Io_Exceptions'Elab_Spec;
      E123 := E123 + 1;
      Ada.Tags'Elab_Spec;
      Ada.Streams'Elab_Spec;
      E122 := E122 + 1;
      Interfaces.C'Elab_Spec;
      System.Exceptions'Elab_Spec;
      E023 := E023 + 1;
      System.Finalization_Root'Elab_Spec;
      E125 := E125 + 1;
      Ada.Finalization'Elab_Spec;
      E120 := E120 + 1;
      System.Storage_Pools'Elab_Spec;
      E145 := E145 + 1;
      System.Finalization_Masters'Elab_Spec;
      System.Task_Info'Elab_Spec;
      E071 := E071 + 1;
      System.Pool_Global'Elab_Spec;
      E147 := E147 + 1;
      System.Finalization_Masters'Elab_Body;
      E139 := E139 + 1;
      E052 := E052 + 1;
      Ada.Tags'Elab_Body;
      E087 := E087 + 1;
      System.Soft_Links'Elab_Body;
      E011 := E011 + 1;
      System.Secondary_Stack'Elab_Body;
      E015 := E015 + 1;
      System.Tasking.Initialization'Elab_Body;
      E116 := E116 + 1;
      Ada.Real_Time'Elab_Spec;
      Ada.Real_Time'Elab_Body;
      E043 := E043 + 1;
      System.Tasking.Protected_Objects'Elab_Body;
      E104 := E104 + 1;
      System.Tasking.Protected_Objects.Entries'Elab_Spec;
      E112 := E112 + 1;
      System.Tasking.Queuing'Elab_Body;
      E131 := E131 + 1;
      System.Tasking.Stages'Elab_Body;
      E151 := E151 + 1;
      E102 := E102 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_main");

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer
   is
      procedure Initialize (Addr : System.Address);
      pragma Import (C, Initialize, "__gnat_initialize");

      procedure Finalize;
      pragma Import (C, Finalize, "__gnat_finalize");
      SEH : aliased array (1 .. 2) of Integer;

      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      gnat_argc := argc;
      gnat_argv := argv;
      gnat_envp := envp;

      Initialize (SEH'Address);
      adainit;
      Ada_Main_Program;
      adafinal;
      Finalize;
      return (gnat_exit_status);
   end;

--  BEGIN Object file/option list
   --   /home/alvaro/Escritorio/UNI/Clase/Sistemas en tiempo real (STR)/workspace/ADA/p3/obj/paquete_buffer.o
   --   /home/alvaro/Escritorio/UNI/Clase/Sistemas en tiempo real (STR)/workspace/ADA/p3/obj/main.o
   --   -L/home/alvaro/Escritorio/UNI/Clase/Sistemas en tiempo real (STR)/workspace/ADA/p3/obj/
   --   -L/home/alvaro/Escritorio/UNI/Clase/Sistemas en tiempo real (STR)/workspace/ADA/p3/obj/
   --   -L/usr/gnat/lib/gcc/x86_64-pc-linux-gnu/4.9.3/adalib/
   --   -static
   --   -lgnarl
   --   -lgnat
   --   -lpthread
   --   -lrt
--  END Object file/option list   

end ada_main;
