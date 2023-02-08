<script lang="ts">
  import LinearProgress from "@smui/linear-progress";
  import IconButton from "@smui/icon-button";
  import Snackbar, { Label, Actions } from "@smui/snackbar";
  import Modal from "../Modal/index.svelte";
  import ws from "../../../services/webSocket";
  import { onMount } from "svelte";
  import { getUpdates } from "../../../services/updateService";
  import "./index.css";

  let isOpened = false;

  let file = "";
  let updatePercentage = 0;

  let updateAssets = [];
  let currentFileIndex = 1;

  let snackbar: Snackbar;

  onMount(() => {
    getUpdates().then(([{ assets }]) => {
      updateAssets = assets.filter((asset) => asset.name !== "firmware.bin");
    });
    ws.onMessage<{ name: string; percentage: number }>(
      "updating",
      ({ name, percentage }) => {
        isOpened = true;
        file = name;
        updatePercentage = percentage;

        if (percentage === 100 && name === "firmware.bin")
          snackbar && snackbar.open();

        currentFileIndex =
          updateAssets.findIndex((asset) => asset.name === name) + 1;
      }
    );
  });
</script>

<Modal {isOpened}>
  <div style="display: flex;justify-content:center;align-items:center">
    <div style="padding: 30px 0;width:80%">
      <div style="margin-bottom: 5px;">
        Baixando {file}... Não tira o controlador da tomada pf
      </div>
      <LinearProgress progress={updatePercentage / 100} />
      <div style="margin:5px 0 30px 0;">{updatePercentage}%</div>
      <div style="margin-bottom:5px">
        Arquivo {currentFileIndex} de {updateAssets.length}
      </div>
      <LinearProgress progress={currentFileIndex / updateAssets.length} />
      <div style="margin-top:5px">
        {(currentFileIndex / updateAssets.length) * 100}%
      </div>
    </div>
  </div>
  <Snackbar bind:this={snackbar}>
    <Label>Reiniciando... Perai que jajá tem mais</Label>
    <Actions>
      <IconButton class="material-icons" title="Dismiss">close</IconButton>
    </Actions>
  </Snackbar>
</Modal>
