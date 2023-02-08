<script lang="ts">
  import SvelteMarkdown from "svelte-markdown";
  import Modal from "../Modal/index.svelte";
  import Button from "@smui/button";
  import { onMount } from "svelte";
  import { getUpdates, startUpdate } from "../../../services/updateService";
  import LoadingIndicator from "../LoadingIndicator/index.svelte";
  import UpdatingModal from "../UpdatingModal/index.svelte";

  export let isOpened: boolean;
  export let toggleModal: () => void;

  let loading = false;

  let updateNotes = "";

  let updateLoading = false;

  const update = async () => {
    updateLoading = true;
    await startUpdate();
    setTimeout(() => {
      updateLoading = false;
    }, 3000);
  };

  onMount(async () => {
    loading = true;

    const updates = await getUpdates();

    updateNotes = updates[0].body.replaceAll("\n", "<br />");

    loading = false;
  });
</script>

<Modal {isOpened}>
  <div
    style="padding:10px 5px;max-height:80vh;text-align:start;display:flex;flex-direction:column;align-items:center"
  >
    <h2>Atualização Disponível</h2>
    <h2 style="margin-left:5%;align-self: flex-start;margin-top:10px">
      Notas de atualização:
    </h2>
    <div style="width:90%;max-height:60%;overflow-y:auto;">
      <SvelteMarkdown options={{}} source={updateNotes} />
    </div>
    <div style="margin:10px 0px">
      <Button on:click={update} style="margin-right:10px" variant="raised"
        >{#if updateLoading}<LoadingIndicator loading={updateLoading} />
        {:else}Atualizar{/if}</Button
      ><Button on:click={toggleModal} variant="text">Fechar</Button>
    </div>
  </div>
  <LoadingIndicator {loading} />
  <UpdatingModal />
</Modal>
