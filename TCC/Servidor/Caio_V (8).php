<?php

// Configurações de conexão com o banco de dados
$host = "localhost";
$usuario = "digitaq_Caio_V";
$senha = "35461375Caio";
$banco = "digitaq_Caio_V";

//definições de valores
$debug = FALSE;
$measurements = array(
    "D" => 1440,
    "S" => 1435,
    "M" => 1426,
    "A" => 1098,
    "T" => 1440
);

// Conexão com o banco de dados
$conn = new mysqli($host, $usuario, $senha, $banco);

// Verifique se houve um erro na conexão
if ($conn->connect_error) {
    die("Erro na conexão: " . $conn->connect_error);
}
// verifica se recebeu o ID
if(isset($_GET['ID'])){
    $ID = $_GET['ID'];
    if($debug)echo "<br>ID: $ID";
    //Verifica se ele existe
    $sql = "SELECT * FROM Monitoramento WHERE ID = '$ID'";
    $result  = $conn->query($sql);
    if($result->num_rows < 1){
        //se não existr uma linha com esse id crie
        $sql = "INSERT INTO `Monitoramento` (`unique_key`, `ID`,
                                            `C_S_1`, `C_S_2`, `C_S_3`, `C_S_4`, `C_S_5`, `C_S_6`, `C_S_7`, `C_S_8`,
                                            `G_D_S_U`, `G_S_S_U`, `G_M_S_U`, `G_A_S_U`, `G_T_S_U`,
                                            `G_D_S_L`, `G_S_S_L`, `G_M_S_L`, `G_A_S_L`, `G_T_S_L`,
                                            `G_D_S_T`, `G_S_S_T`, `G_M_S_T`, `G_A_S_T`, `G_T_S_T`,
                                            `G_D_A_U`, `G_S_A_U`, `G_M_A_U`, `G_A_A_U`, `G_T_A_U`,
                                            `G_D_A_L`, `G_S_A_L`, `G_M_A_L`, `G_A_A_L`, `G_T_A_L`,
                                            `G_D_A_T`, `G_S_A_T`, `G_M_A_T`, `G_A_A_T`, `G_T_A_T`)
                                            VALUES (NULL, '$ID',
                                            '', '', '', '', '', '', '', '', '',
                                            '', '', '', '', '', '', '', '', '', '',
                                            '', '', '', '', '', '', '', '', '', '',
                                            '', '', '', '', '', '', '', '', '')";
        $conn->query($sql);
        // e configure
        $sql = "";
        for($i = 1; $i <= 8; $i++){
            $conn->query("UPDATE Monitoramento SET C_S_".$i." = REPEAT('0,',57) WHERE `ID` = '$ID';");
        }
        $letter = array("S_U","S_L","S_T","A_U","A_L","A_T");
        for($i = 0; $i < 6; $i++){
            $conn->query("UPDATE Monitoramento SET G_D_".$letter[$i]." = REPEAT('0,',".($measurements["D"]*8).") WHERE `ID` = '$ID';");
            $conn->query("UPDATE Monitoramento SET G_S_".$letter[$i]." = REPEAT('0,',".($measurements["S"]*8).") WHERE `ID` = '$ID';");
            $conn->query("UPDATE Monitoramento SET G_M_".$letter[$i]." = REPEAT('0,',".($measurements["M"]*8).") WHERE `ID` = '$ID';");
            $conn->query("UPDATE Monitoramento SET G_A_".$letter[$i]." = REPEAT('0,',".($measurements["A"]*8).") WHERE `ID` = '$ID';");
            $conn->query("UPDATE Monitoramento SET G_T_".$letter[$i]." = REPEAT('0,',".($measurements["T"]*8).") WHERE `ID` = '$ID';");
        }
    }
    
    
    
    //(ID, Values, Address, Time_space)
	//Values = float[24]
	//address = enderço do array
	//Time_space = ("D", "M", "S","A","T") (Dia, Mes, Semana, Ano, Tudo)
	//www.digitaq.com.br/Caio_V.php?ID=1&Values=0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,&Address=3&Time_space=S
    if(isset($_GET['Values']) && isset($_GET['Address']) && isset($_GET['Time_space'])){
        $Values      =  $_GET['Values'];         if($debug)echo "<br>Values: $Values";
        $Address    =  $_GET['Address'];       if($debug)echo "<br>Address: $Address";
        $Time_space =  $_GET['Time_space'];    if($debug)echo "<br>time space: $Time_space";
        
        $map_module = array("S_U","S_L","S_T","A_U","A_L","A_T");
        
        for($Module = 0; $Module < 6; $Module++){
            for($Index = 0; $Index < 8; $Index++){
                //verifica se existe uma tabela com o ID
                $sql = "SELECT * FROM Monitoramento WHERE ID = '$ID'";
                $result  = $conn->query($sql);
                //se não existir, encerrar
                if($result->num_rows < 1)exit();
                
                //seleciona a coluna certa
                $row = $result->fetch_assoc();
                $Values_ = explode(',', $Values);
                
                $serialized_array = $row["G_".$Time_space."_".$map_module[$Module]];
                if($debug)echo "<br>G_".$Time_space."_".$map_module[$Module];
                if($debug)echo " Index: ".$Index;
                $array = explode(',', $serialized_array);
                
                $Final_address = $Address + ($Index*$measurements[$Time_space]);
                //verifica se o endereço está dentro das bordas do array
                if (isset($array[$Final_address])){
                    //sava o novo valor no array
                    if($debug)echo "<br> Final_address: ".$Final_address;
                    $array[$Final_address] = round($Values_[($Index*6)+$Module], 1);
                    if($debug)echo "<br> Value: ".$array[$Final_address];
                    //Serializa o array de volta para uma string usando implode
                    
                    $serialized_array = implode(',', $array);
                    if($debug)echo "<br> UPDATE Monitoramento SET G_".$Time_space."_".$map_module[$Module]." = '$serialized_array' WHERE ID = '$ID'";
                    //executa a query para salvar o novo array
                    $result = $conn->query("UPDATE Monitoramento SET G_".$Time_space."_".$map_module[$Module]." = '$serialized_array' WHERE ID = '$ID'"); 
                   
                    // verifica o resultado da query
                    if($result === TRUE){
                        //funcionou
                        if($debug)echo "<br>OK";
                    }else{
                        //não funcionou
                        if($debug)echo "<br>ERROR";
                    }
                }else{
                    //endereço exede o tamanho do array
                    if($debug)echo "<br>ERROR: array out of bound!";
                }
            }
        }
        
        
        
    }

    
    
    //(ID, Config, Sub_sector)
	//ID - id do esp32
    //Config = "(48char)+(6char)"
	//Sub_sector = qual dos 8 sub-setores modificar
	//www.digitaq.com.br/Caio_V.php?ID=1&Sub_sector=2&Module=000000000000000000000000000000000000000000000000000
	if(isset($_GET['Module']) && isset($_GET['Sub_sector']) && !isset($_GET['Value'])){
	    $Module = $_GET['Module'];           if($debug)echo "Module: $Module";
	    $Sub_sector = $_GET['Sub_sector'];   if($debug)echo "<br>Sub Sector: $Sub_sector";
	    
	    
	    //verifica se existe uma tabela com o ID
        $sql = "SELECT * FROM Monitoramento WHERE ID = '$ID'";
        $result  = $conn->query($sql);
        //se não existir, encerrar
        if($result->num_rows < 1)die("<br>Not able to find a row whit the ID: $ID!");

        //separa a string em um array
        $array = str_split($Module);
        
        if (count($array) != 57) {
            if (count($array) < 57) {
                //Adiciona elementos até que o tamanho seja 48
                while (count($array) < 57) {
                    $array[] = '0';
                }
            } else {
                //Reduz o tamanho para 48 elementos
                $array = array_slice($array, 0, 57);
            }
        }
        
        if($debug)echo "<br> array: ".implode($array);
        
        //Serializa o array de volta para uma string usando implode
        $serialized_array = implode(',', $array);
        
        //executa a query para salvar o novo array
        $result = $conn->query("UPDATE Monitoramento SET C_S_".$Sub_sector." = '$serialized_array' WHERE ID = '$ID'"); 
       
        //se a query foi bem sucedida
        if($result === TRUE){
            //funcionou
            if($debug)echo "<br>OK";
        }else{
            //não funcionou
           if($debug)echo "<br>ERROR: $conn->error";
        }
	}
	
	
	
	//(ID, Module, Sub_sector, Value, Config, Time)
	//ID - id do esp32
	//Module = ("S_U", "A_T", ...)[Sensor de Umidade, Atuador de Temperatura]
	//Sub_sector = qual dos 8 sub-setores modificar
	//Config = modo de comparação (manter (>) ou (<), ou manter por tempo em Horas (H))
	//Value = valor
	//Time = tempo que o atuador fica ativo com 10s de precisão
	//www.digitaq.com.br/Caio_V.php?ID=1&Module=U&Sub_sector=2&Value=40&Config=>&Time=9
	if(isset($_GET['Module']) && isset($_GET['Sub_sector']) && isset($_GET['Value']) && isset($_GET['Config']) && isset($_GET['Time'])){
	    $Module = $_GET['Module'];            if($debug)echo "Module: $Module";
	    $Sub_sector = $_GET['Sub_sector'];    if($debug)echo "<br>Sub Sector: $Sub_sector";
	    $Value = $_GET['Value'];              if($debug)echo "<br> Value: $Value";
	    $Config = urldecode($_GET['Config']); if($debug)echo "<br>Config: $Config";
	    $Time = urldecode($_GET['Time']);     if($debug)echo "<br>Time: $Time";
	    
	    $map = array(
	        "U" => 0,
	        "L" => 3,
	        "T" => 6,
	        );
	    
	    //verifica se existe uma tabela com o ID
        $sql = "SELECT * FROM Monitoramento WHERE ID = '$ID'";
        $result  = $conn->query($sql);
        //se não existir, encerrar
        if($result->num_rows < 1)die("<br>Not able to find a row whit the ID: $ID!");
        
        //seleciona a coluna certa
        $row = $result->fetch_assoc();
        $serialized_array = $row["C_S_".$Sub_sector];
        if($debug)echo "<br>C_S_".$Sub_sector;
        
        //deserealiza o array
        $array = explode(',', $serialized_array);
        
        $Final_addres = $map[$Module] + 48;
        if($debug)echo "<br> final address: $Final_addres";
        
        if(isset($array[$Final_addres]) && isset($array[$Final_addres+1])){
            //monta o enderoço real 
            $array[$Final_addres] = $Value;
            $array[$Final_addres+1] = $Config;
            $array[$Final_addres+2] = $Time;
            
            //Serializa o array de volta para uma string usando implode
            $serialized_array = implode(',', $array);
            
            //executa a query para salvar o novo array
            $result = $conn->query("UPDATE Monitoramento SET C_S_".$Sub_sector." = '$serialized_array' WHERE ID = '$ID'"); 
           
            //se a query foi bem sucedida
            if($result === TRUE){
                //funcionou
                if($debug)echo "<br>OK";
            }else{
                //não funcionou
                if($debug)echo "<br>ERROR: $conn->error";
            }
        }else{
            //endereço exede o tamanho do array
            if($debug)echo "<br>ERROR: array out of bound!";
        }
	}
	
	
	
	//(ID, Sub_sector)
	//ID - id do esp32
	//Sub_sector = qual dos 8 sub-setores
    //www.digitaq.com.br/Caio_V.php?ID=1&Sub_sector=2
    if(isset($_GET['Sub_sector']) && !isset($_GET['Module'])){
        $Sub_sector = $_GET['Sub_sector']; if($debug)echo "sub-sector: $Sub_sector";
        
        //seleciona a linha   
        $result = $conn->query("SELECT * FROM Monitoramento WHERE ID = '$ID'");
        if($result->num_rows < 1)die("<br>Not able to find a row whit the ID: $ID!");
        
        //seleciona a coluna 
        $row = $result->fetch_assoc();
        $serialized_array = $row["C_S_".($Sub_sector)];
        if($debug)echo "<br>C_S_".($Sub_sector)."<br>";
        
        if(isset($_GET["APP"])){
            echo $serialized_array;
        }else{
            //remove as virgulas do array
            $array = explode(',',$serialized_array);
            $out = "";
            
            for($i = 0; $i < 48; $i++){
                $out .= $array[$i];
            }
            for($i = 48; $i < 57; $i++){
                if(is_numeric($array[$i])){
                    $out .= chr($array[$i]);
                }else{
                     $out .= $array[$i];
                }
            }
            
            //retorna o array para o cliente
            echo $out;   
        }
	}
	
	
	
    //(ID, Grafico, espaco_de_tenpo)
	//ID - id do esp32
	//Graf = ("S_U", "A_T" ...)
	//Time_space = ("D", "S", "M",...)
	//Index = qual dos 8 modulos
	//www.digitaq.com.br/Caio_V.php?ID=1&Graf=S_U&Time_space=D&Index=0
	if(isset($_GET['Graf']) && isset($_GET['Time_space']) && isset($_GET['Index'])){
	    $Graf       = $_GET['Graf'];         if($debug)echo "Graf: $Graf";
	    $Time_space = $_GET['Time_space'];   if($debug)echo "<br>Time space: $Time_space";
	    $Index      = $_GET['Index'];        if($debug)echo "<br> Index: $Index";
	    
	    $sql = "SELECT * FROM Monitoramento WHERE ID = '$ID'";
        $result  = $conn->query($sql);
        //se não existir, encerrar
        if($result->num_rows < 1)die("<br>Not able to find a row whit the ID: $ID!");
        
        //seleciona a coluna certa
        $row = $result->fetch_assoc();
        $serialized_array = $row["G_".$Time_space."_".$Graf];
        if($debug)echo "<br>G_".$Time_space."_".$Graf."<br>";
        
        //deserealiza o array
        $array = explode(',', $serialized_array);
        
        $start_index = $Index*$measurements[$Time_space];
        $length        = $measurements[$Time_space];
        
        if(isset($array[$start_index]) && isset($array[$start_index+$length])){
            
            $slice = array_slice($array, $start_index, $length);
            $response = implode(',', $slice);
            echo $response;
        }else{
            
            if($debug)echo "<br>Array out of bound! start: $start_index; length: $length";
	    }
	    
	}
	
}

//Fecha a conexão com o banco de dados
$conn->close();

?>