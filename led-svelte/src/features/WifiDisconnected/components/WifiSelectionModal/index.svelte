<script lang="ts">
  import Snackbar, { Actions } from "@smui/snackbar";
  import IconButton from "@smui/icon-button";
  import Button, { Label } from "@smui/button";
  import { Icon } from "@smui/common";
  import Textfield from "@smui/textfield";

  import type { Wifi } from "../../../../shared/@types/Wifi";
  import { connectToWifi } from "../../../../services/connectionService";
  import Modal from "../../../../shared/components/Modal/index.svelte";
  import LoadingIndicator from "../../../../shared/components/LoadingIndicator/index.svelte";
  import ws from "../../../../services/webSocket";
  import connectionStore from "../../../../shared/stores/connection";

  import "./index.css";
  import { onMount } from "svelte";

  let loading = false;

  let snackbarError: Snackbar;
  let hasSnackbarError = false;

  export let wifi: Wifi;
  export let isOpened = false;
  const closeModal = () => (isOpened = false);

  let showPassword = false;
  const switchPasswordVisibility = () => (showPassword = !showPassword);

  let password = "";

  let errorTimeout: number;

  const connect = () => {
    loading = true;

    connectToWifi(wifi.name, password);

    errorTimeout = setTimeout(() => {
      hasSnackbarError = true;
      setTimeout(() => {
        hasSnackbarError = false;
      }, 3000);
      snackbarError.open();
      loading = false;
    }, 6000);
  };

  onMount(() => {
    ws.onMessage("wifiConnected", () => {
      connectionStore.update((state) => ({
        ...state,
        isConnected: true,
      }));
      loading = false;
      errorTimeout && clearTimeout(errorTimeout);
      closeModal();
    });
  });
</script>

<Modal bind:isOpened>
  <div>
    <h4>Conectar à rede {wifi.name}</h4>
    <p>Intensidade do sinal: {wifi.signal}</p>
    <div
      style="display:flex;align-items:center;justify-content:center; margin-bottom: 10px;"
    >
      <Textfield
        type={showPassword ? "text" : "password"}
        bind:value={password}
        label="Senha"
        variant="outlined"
        style="margin-right: 10px;"
      />
      <IconButton on:click={switchPasswordVisibility}
        ><Icon class="material-icons"
          >{showPassword ? "visibility_off" : "visibility"}</Icon
        ></IconButton
      >
    </div>
    <div style="margin-bottom:20px">
      <Button style="margin-right:20px" variant="raised" on:click={connect}
        >{#if loading}<LoadingIndicator bind:loading />{:else}<Label
            >Conectar</Label
          >{/if}</Button
      >
      <Button variant="text" on:click={closeModal}
        ><Label>Cancelar</Label></Button
      >
    </div>
  </div>
  <Snackbar
    bind:this={snackbarError}
    class="demo-error"
    style={`${hasSnackbarError ? "" : "display:none;"}`}
  >
    <Label>Não foi possível conectar à {wifi.name}.</Label>
    <Actions>
      <IconButton class="material-icons" title="Dismiss">close</IconButton>
    </Actions>
  </Snackbar>
</Modal>
