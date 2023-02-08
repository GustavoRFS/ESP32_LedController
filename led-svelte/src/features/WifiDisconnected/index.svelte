<script lang="ts">
  import "./index.css";
  import ws from "../../services/webSocket";
  import Button from "@smui/button";
  import DataTable, { Head, Body, Row, Cell } from "@smui/data-table";
  import WifiSelectionModal from "./components/WifiSelectionModal/index.svelte";
  import type { Wifi } from "../../shared/@types/Wifi";
  import { onMount } from "svelte";

  export let onIgnore: () => void;

  let wifis: Wifi[] = [{ name: "Rede 1", signal: 100 }];

  onMount(() => {
    ws.onMessage<Wifi[]>("wifiScan", (data) => {
      wifis = data.map((wifi) => ({
        ...wifi,
        signal: wifi.signal > 100 ? 100 : wifi.signal,
      }));
    });
  });

  let isOpened = false;
  let selectedWifi = null;

  const openModal = (index: number) => {
    selectedWifi = wifis[index];
    isOpened = true;
  };
</script>

<div style="display:flex;flex-direction:column;max-width:95vw">
  <WifiSelectionModal bind:wifi={selectedWifi} bind:isOpened />
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
      {#each wifis as wifi, index}
        <Row on:click={() => openModal(index)} class="wifi-item">
          <Cell>{wifi.name}</Cell>
          <Cell>{wifi.signal}%</Cell>
        </Row>
      {/each}</Body
    >
  </DataTable>
  <Button on:click={onIgnore} style="margin-top:5px" variant="text"
    >Usar sem Wifi</Button
  >
</div>
