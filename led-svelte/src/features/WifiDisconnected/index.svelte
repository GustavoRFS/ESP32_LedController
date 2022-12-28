<script lang="ts">
  import "./index.css"
  import DataTable, { Head, Body, Row, Cell } from '@smui/data-table';
  import WifiSelectionModal from './components/WifiSelectionModal/index.svelte'
  import type { Wifi } from "../../shared/@types/Wifi";
  
  let wifis:Wifi[]=[{name:"Wifi 1",signal:100},{name:"Wifi 2",signal:80},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},{name:"Wifi 3",signal:50},]
  let isOpened=false;
  let selectedWifi=null;

  const openModal =(index:number)=>{
    selectedWifi=wifis[index];
    isOpened=true;
  }
</script>

<div >
  <WifiSelectionModal bind:wifi={selectedWifi} bind:isOpened={isOpened}  />
  <h2>Controlador está desconectado do wifi</h2>
  <p>Selecione uma das redes a seguir:</p>
  <DataTable style="max-height:50vh">
    <Head>
      <Row>
        <Cell>Nome da rede</Cell>
        <Cell>Intensidade do sinal</Cell>
      </Row>
    </Head>
    <Body>
    {#each wifis as wifi,index }
    <Row  on:click={()=>openModal(index)} class="wifi-item">
      <Cell>{wifi.name}</Cell>
      <Cell>{wifi.signal}%</Cell>
    </Row>
    {/each}</Body>
  </DataTable>
</div>